/*
 * Copyright (C) 2022 Polygon Zone Open Source Organization .
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http:// www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 *
 * limitations under the License.
 */

#include "utils_file.h"
#include "file_reader.h"

typedef struct
{
    bool close_fd;
    int fd;
    size_t len;
    size_t pos;
    char buf[20];
} mp_reader_custom_t;

static const char* file_name_checker(const char* filename)
{
    return ((filename[0] == '.') && (filename[1] == '/')) ? (filename + 2) : filename;
}

static mp_uint_t mp_reader_custom_readbyte(void* data)
{
    mp_reader_custom_t* reader = (mp_reader_custom_t*)data;
    mp_uint_t ret = MP_READER_EOF;
    
    if( reader->pos >= reader->len )
    {
        if( reader->len > 0 )
        {
            MP_THREAD_GIL_EXIT();
            
            int n = UtilsFileRead(reader->fd, reader->buf, sizeof(reader->buf));
            
            MP_THREAD_GIL_ENTER();
            
            if( n > 0 )
            {
                reader->pos = 0;
                reader->len = n;
                
                ret = reader->buf[reader->pos++];
            }
            else
            {
                reader->len = 0;
                
                ret = MP_READER_EOF;
            }
        }
    }
    else
    {
        ret = reader->buf[reader->pos++];
    }
    
    return ret;
}

static void mp_reader_custom_close(void* data) 
{
    mp_reader_custom_t* reader = (mp_reader_custom_t*)data;
    
    if( reader->close_fd )
    {
        MP_THREAD_GIL_EXIT();
        
        UtilsFileClose(reader->fd);
        
        MP_THREAD_GIL_ENTER();
    }
    
    m_del_obj(mp_reader_custom_t, reader);
}

void mp_reader_new_file_from_fd(mp_reader_t* reader, int fd, bool close_fd)
{
    mp_reader_custom_t* rp = m_new_obj(mp_reader_custom_t);
    
    rp->close_fd = close_fd;
    rp->fd = fd;
    
    MP_THREAD_GIL_EXIT();
    
    int n = UtilsFileRead(rp->fd, rp->buf, sizeof(rp->buf));

    if( n == -1 )
    {
        if( close_fd )
        {
            UtilsFileClose(fd);
        }
        
        MP_THREAD_GIL_ENTER();
        
        mp_raise_OSError(errno);
    }
    
    MP_THREAD_GIL_ENTER();
    
    rp->len = n;
    rp->pos = 0;
    
    reader->data = rp;
    reader->readbyte = mp_reader_custom_readbyte;
    reader->close = mp_reader_custom_close;
}






void mp_reader_new_file(mp_reader_t* reader, const char* filename)
{
    MP_THREAD_GIL_EXIT();
    
    int fd = UtilsFileOpen(file_name_checker(filename), O_RDONLY_FS, 0);
      
    MP_THREAD_GIL_ENTER();
    
    if( fd < 0)
    {
        mp_raise_OSError(errno);
    }
    
    mp_reader_new_file_from_fd(reader, fd, true);
}
/*
mp_lexer_t* mp_lexer_new_from_file(const char* filename)
{
    mp_reader_t reader = {0};
    
    mp_reader_new_file(&reader, file_name_checker(filename));
    
    return mp_lexer_new(qstr_from_str(file_name_checker(filename)), reader);
}
*/
mp_import_stat_t mp_import_stat(const char* path)
{
    mp_import_stat_t ret = MP_IMPORT_STAT_NO_EXIST;
    
    int fd = UtilsFileOpen(file_name_checker(path), O_RDONLY_FS, 0);
    
    if( fd > 0 )
    {
        ret = MP_IMPORT_STAT_FILE;
        UtilsFileClose(fd);
    }
     
    return ret;
}

