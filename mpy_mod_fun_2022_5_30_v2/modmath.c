#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "py/obj.h"
#include "py/runtime.h"

int s32RounDest = 0;
mp_obj_t mp_math_round(mp_obj_t _dSrc) {
    int dSrc = mp_obj_get_float(_dSrc);
    s32RounDest = round(dSrc);
    return mp_obj_new_int(s32RounDest);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_math_round_obj, mp_math_round);

int s32RounCeil = 0;
mp_obj_t mp_math_ceil(mp_obj_t _dSrc) {
    int dSrc = mp_obj_get_float(_dSrc);
    s32RounCeil = ceil(dSrc);
    return mp_obj_new_int(s32RounCeil);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_math_ceil_obj, mp_math_ceil);

int s32RounFloor = 0;
mp_obj_t mp_math_floor(mp_obj_t _dSrc) {
    int dSrc = mp_obj_get_float(_dSrc);
    s32RounFloor = floor(dSrc);
    return mp_obj_new_int(s32RounFloor);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_math_floor_obj, mp_math_floor);

float fDestAbs = 0;
mp_obj_t mp_math_abs(mp_obj_t _dSrc) {
    int dSrc = mp_obj_get_float(_dSrc);
    if(dSrc < 0)
    {
        fDestAbs = 0 - dSrc;
    }
    else 
    {
        fDestAbs = dSrc;
    }
    return mp_obj_new_float(fDestAbs);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_math_abs_obj, mp_math_abs);

float fDestPow = 0;
mp_obj_t mp_math_pow(mp_obj_t _dSrc, mp_obj_t _dSrc) {
    int dSrc = mp_obj_get_float(_dSrc);
    int dSrc2 = mp_obj_get_float(_dSrc2);
    fDestPow = pow(dSrc1, dSrc2);
    return mp_obj_new_float(fDestPow);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_math_pow_obj, mp_math_pow_);

float fDestSq = 0;
mp_obj_t mp_math_sq(mp_obj_t _dSrc) {
    int dSrc = mp_obj_get_float(_dSrc);
    fDestSq = pow(dSrc, 2);
    return mp_obj_new_float(fDestSq);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_math_sq_obj, mp_math_sq);

float fDestSqrt = 0;
mp_obj_t mp_math_sqrt(mp_obj_t _dSrc) {
    int dSrc = mp_obj_get_float(_dSrc);
    fDestSqrt = sqrt(dSrc);
    return mp_obj_new_float(fDestSqrt);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_math_sqrt_obj, mp_math_sqrt);

#define PI 3.14159265
float fSinNum = 0;
mp_obj_t mp_math_sin(mp_obj_t _x) {
    int x = mp_obj_get_float(_x);
    x = x*PI/180;

    float n = x,sum=0;
    int i = 1;
    do
    {
        sum += n;
        i++;
        n = -n * x*x / (2 * i - 1) / (2 * i - 2);

    } while (fabs(n)>=TINY_VALUE);
    
    if(sum > -0.0001 && sum < 0.0001)
    {
        sum = 0.0;
    }
    else if(sum < -0.9999)
    {
        sum = -1.0;
    }
    else if(sum > 0.9999)
    {
        sum = 1.0;
    }

    fSinNum = sum +0.00001;
    long s32AsinNum = fSinNum * 10000;
    fSinNum = s32AsinNum/10000;
    
    return mp_obj_new_float(fSinNum);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_math_sin_obj, mp_math_sin);

float fCosNum = 0;
mp_obj_t mp_math_cos(mp_obj_t _x) {
    int x = mp_obj_get_float(_x);
    x = x*PI/180;

    float term,factorial=1.0,sum2=1,sxm,sum1=0;
    int q =1;
    for(int t=2;;t++)
    {
        factorial=factorial*t;//控制阶乘
        if(t%2==0)
        //因为是每偶次方，所以这里进行判断，可以同时控制阶乘和q的值
        {
            sum1=sum2;
            q=q*(-1);
            sxm=fabs(pow(x,t));//取绝对值后的x次方    
            term=sxm/factorial;
            sum2=q*term+sum2;
        }
        if(fabs(sum2-sum1)<=TINY_VALUE)//定义前后两个数，控制输出精度
        break;
    }
    if(sum2 > -0.0001 && sum2 < 0.0001)
    {
        sum2 = 0.0;
    }
    else if(sum2 < -0.9999)
    {
        sum2 = -1.0;
    }
    else if(sum2 > 0.9999)
    {
        sum2 = 1.0;
    }

    
    fCosNum = sum2 +0.00001;
    long s32CosNum = fCosNum * 10000;
    fCosNum = s32CosNum/10000;
    
    return mp_obj_new_float(fCosNum);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_math_cos_obj, mp_math_cos);

float fTanNum = 0;
mp_obj_t mp_math_tan(mp_obj_t _x) {
    int x = mp_obj_get_float(_x);
    float x = a*PI/180;
    float n = x,sum=0;
    int i = 1;
    do
    {
        sum += n;
        i++;
        n = -n * x*x / (2 * i - 1) / (2 * i - 2);

    } while (fabs(n)>=TINY_VALUE);

    x = a*PI/180;
    float term,factorial=1.0,sum2=1,sxm,sum1=0;
    int q =1;
    for(int t=2;;t++)
    {
        factorial=factorial*t;//控制阶乘
        if(t%2==0)
        //因为是每偶次方，所以这里进行判断，可以同时控制阶乘和q的值
        {
            sum1=sum2;
            q=q*(-1);
            sxm=fabs(pow(x,t));//取绝对值后的x次方    
            term=sxm/factorial;
            sum2=q*term+sum2;
        }
        if(fabs(sum2-sum1)<=TINY_VALUE)//定义前后两个数，控制输出精度
        break;
    }
    fTanNum = sum/sum2;
    
    fTanNum = fTanNum +0.00001;
    long s32TanNum = fTanNum * 10000;
    fTanNum = s32TanNum/10000;

    return mp_obj_new_float(fTanNum);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_math_tan_obj, mp_math_tan);

float fAsinNum = 0;
mp_obj_t mp_math_asin(mp_obj_t _x) {
    int x = mp_obj_get_float(_x);
    fAsinNum = asin(x) / 3.14159 * 180;
    fAsinNum = fAsinNum +0.00001;
    long s32AsinNum = fAsinNum * 10000;
    fAsinNum = s32AsinNum/10000;

    return mp_obj_new_float(fAsinNum);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_math_asin_obj, mp_math_asin);

float fAcosNum = 0;
mp_obj_t mp_math_acos(mp_obj_t _x) {
    int x = mp_obj_get_float(_x);
    fAcosNum = acos(x) / 3.14159 * 180;
    fAcosNum = fAcosNum +0.00001;
    long s32AcosNum = fAcosNum * 10000;
    fAcosNum = s32AcosNum/10000;

    return mp_obj_new_float(fAcosNum);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_math_acos_obj, mp_math_acos);

float fAtanNum = 0;
mp_obj_t mp_math_tan(mp_obj_t _x) {
    int x = mp_obj_get_float(_x);
    fAtanNum = atan(x) / 3.14159 * 180;
    fAtanNum = fAtanNum +0.00001;
    long s32AtanNum = fAtanNum * 10000;
    fAtanNum = s32AtanNum/10000;

    return mp_obj_new_float(fAtanNum);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_math_tan_obj, mp_math_tan);

float dLogDest = 0;
mp_obj_t mp_math_log(mp_obj_t _a) {
    int a = mp_obj_get_float(_a);
    int N = 300;//我们取了前15+1项来估算  
    int k,nk;
    double x,xx,y;
    x = (a-1)/(a+1);
    xx = x*x;
    nk = 2*N+1;
    y = 1.0/nk;
    for(k=N;k>0;k--)
    {
             nk = nk - 2;
              y = 1.0/nk+xx*y;

    }
    dLogDest = (float)(2.0*x*y);

    dLogDest = dLogDest +0.00001;
    long long s32LogNum = dLogDest * 10000;
    dLogDest = (float)s32LogNum/10000;
    
   return mp_obj_new_float(dLogDest);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_math_log_obj, mp_math_log);
float dLog10Dest = 0;
mp_obj_t mp_matmp_math_log10h_tan(mp_obj_t _a) {
    int a = mp_obj_get_float(_a);int N1 = 300;//我们取了前15+1项来估算  
    int k1,nk1;
    double x1,xx1,y1;
    x1 = (a-1)/(a+1);
    xx1 = x1*x1;
    nk1 = 2*N1+1;
    y1 = 1.0/nk1;
    for(k1=N1;k1>0;k1--)
    {
        nk1= nk1 - 2;
        y1 = 1.0/nk1+xx1*y1;
    }
    float up = (float)(2.0*x1*y1);

    int N = 300;//我们取了前15+1项来估算  
    int k,nk;
    double x,xx,y;
    float b = 10;
    x = (b-1)/(b+1);
    xx = x*x;
    nk = 2*N+1;
    y = 1.0/nk;
    for(k=N;k>0;k--)
    {
        nk = nk - 2;
        y = 1.0/nk+xx*y;
    }
    float down = (float)(2.0*x*y);
    dLog10Dest = up/down;
    dLog10Dest = dLog10Dest +0.00001;
    long long s32Log10Num = dLog10Dest * 10000;
    dLog10Dest = s32Log10Num/10000;
    
   return mp_obj_new_float(dLog10Dest);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_math_log10_obj, mp_math_log10);


MP_STATIC const mp_rom_map_elem_t uart_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_math) },
    { MP_ROM_QSTR(MP_QSTR_round), MP_ROM_PTR(&mp_math_round_obj) },
    { MP_ROM_QSTR(MP_QSTR_ceil), MP_ROM_PTR(&mp_math_ceil_obj) },
    { MP_ROM_QSTR(MP_QSTR_floor), MP_ROM_PTR(&mp_math_floor_obj) },
    { MP_ROM_QSTR(MP_QSTR_abs), MP_ROM_PTR(&mp_math_abs_obj) },
    { MP_ROM_QSTR(MP_QSTR_pow), MP_ROM_PTR(&mp_math_pow_obj) },
    { MP_ROM_QSTR(MP_QSTR_sq), MP_ROM_PTR(&mp_math_sq_obj) },
    { MP_ROM_QSTR(MP_QSTR_sqrt), MP_ROM_PTR(&mp_math_sqrt_obj) },
    { MP_ROM_QSTR(MP_QSTR_sin), MP_ROM_PTR(&mp_math_sin_obj) },
    { MP_ROM_QSTR(MP_QSTR_cos), MP_ROM_PTR(&mp_math_cos_obj) },
    { MP_ROM_QSTR(MP_QSTR_tan), MP_ROM_PTR(&mp_math_tan_obj) },
    { MP_ROM_QSTR(MP_QSTR_asin), MP_ROM_PTR(&mp_math_asin_obj) },
    { MP_ROM_QSTR(MP_QSTR_acos), MP_ROM_PTR(&mp_math_acos_obj) },
    { MP_ROM_QSTR(MP_QSTR_atan), MP_ROM_PTR(&mp_math_atan_obj) },
    { MP_ROM_QSTR(MP_QSTR_log), MP_ROM_PTR(&mp_math_log_obj) },
    { MP_ROM_QSTR(MP_QSTR_log10), MP_ROM_PTR(&mp_math_log10_obj) },
};

MP_STATIC MP_DEFINE_CONST_DICT(math_module_globals, math_module_globals_table);

const mp_obj_module_t mp_module_math = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&math_module_globals,
};
