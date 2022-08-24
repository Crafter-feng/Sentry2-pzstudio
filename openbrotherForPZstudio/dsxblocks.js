/*
 * Copyright (C) 2022 PolygonZone Open Source Organization .
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
Blockly.Blocks['event_main_thread'] = {
    
    init: function() {
        this.jsonInit({
          "message0": "主程序",
          "colour": "#E9D521",
          "category": Blockly.Categories.event,
          "extensions": ["shape_hat"]
        });
      }
};
Blockly.Blocks['event_sub_thread'] = {
    /**
     * Block to send a broadcast.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "线程",
        "colour": "#E9D521",
        "category": Blockly.Categories.event,
        "extensions": ["shape_hat"]
      });
    }
};
Blockly.Blocks['motion_dsx_temperature'] = {
      
    init: function() {
      this.jsonInit({
        "message0": "读取温度",
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_dsx_humi'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "读取湿度",
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_dsx_get_light'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "获取光敏传感器数值",
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_dsx_beep_init'] = {
  
  init: function() {
    this.jsonInit({
      "message0": "初始化蜂鸣器",
      "category": Blockly.Categories.motion,
      "colour": "#24B0E0",
      "extensions": ["shape_statement"]
    });
  }
};
Blockly.Blocks['motion_dsx_beep_on'] = {
  
  init: function() {
    this.jsonInit({
      "message0": "打开蜂鸣器",
      "category": Blockly.Categories.motion,
      "colour": "#24B0E0",
      "extensions": ["shape_statement"]
    });
  }
};
Blockly.Blocks['motion_dsx_beep_off'] = {
  
  init: function() {
    this.jsonInit({
      "message0": "关闭蜂鸣器",
      "category": Blockly.Categories.motion,
      "colour": "#24B0E0",
      "extensions": ["shape_statement"]
    });
  }
};
Blockly.Blocks['motion_dsx_init_key'] = {
  
  init: function() {
    this.jsonInit({
      "message0": "初始化按键 %1",
      "args0": [
        {
            "type": "field_dropdown",
            "name": "INDEX",
            "options": [
              ['1', '0'],
              ['2', '1'],
            ]
        }
      ],
      "category": Blockly.Categories.motion,
      "colour": "#24B0E0",
      "extensions": ["shape_statement"]
    });
  }
};
Blockly.Blocks['motion_dsx_get_key'] = {
  
  init: function() {
    this.jsonInit({
        "message0": "按键 %1 被 %2 ?",
        "args0": [
          {
              "type": "field_dropdown",
              "name": "INDEX",
              "options": [
                ['A', '0'],
                ['B', '1'],
              ]
          },{
              "type": "field_dropdown",
              "name": "STATE",
              "options": [
                ['按下', '0'],
                ['释放', '1'],
              ]
          }
        ],
      "category": Blockly.Categories.motion,
      "colour": "#24B0E0",
      "extensions": ["output_boolean"]
    });
  }
};
Blockly.Blocks['motion_dsx_icm_init'] = {
  
  init: function() {
    this.jsonInit({
      "message0": "初始化IMU",
      "category": Blockly.Categories.motion,
      "colour": "#24B0E0",
      "extensions": ["shape_statement"]
    });
  }
};
Blockly.Blocks['motion_dsx_read_acc'] = {
  
  init: function() {
    this.jsonInit({
      "message0": "读取加速度计数据",
      "category": Blockly.Categories.motion,
      "colour": "#24B0E0",
      "extensions": ["output_number"]
    });
  }
};
Blockly.Blocks['motion_dsx_read_gyro'] = {
  
  init: function() {
    this.jsonInit({
      "message0": "读取陀螺仪数据",
      "category": Blockly.Categories.motion,
      "colour": "#24B0E0",
      "extensions": ["output_number"]
    });
  }
};
Blockly.Blocks['motion_dsx_read_a'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "读取 %1 轴加速度",
        "args0":[
            {
                "type": "field_dropdown",
                "name": "INDEX",
                "options": [
                  ["X", '0'],
                  ["Y", '1'],
                  ["Z", '2']
                ]
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_dsx_read_g'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "读取 %1 轴角速度",
        "args0":[
            {
                "type": "field_dropdown",
                "name": "INDEX",
                "options": [
                  ["X", '0'],
                  ["Y", '1'],
                  ["Z", '2']
                ]
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_dsx_read_angle'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "读取 %1 轴角度",
        "args0":[
            {
                "type": "field_dropdown",
                "name": "INDEX",
                "options": [
                  ["X", '0'],
                  ["Y", '1'],
                  ["Z", '1']
                ]
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_dsx_oled_init'] = {
  
  init: function() {
    this.jsonInit({
      "message0": "初始化显示屏",
      "category": Blockly.Categories.motion,
      "colour": "#24B0E0",
      "extensions": ["shape_statement"]
    });
  }
};
Blockly.Blocks['motion_dsx_oled_flush'] = {
  
  init: function() {
    this.jsonInit({
      "message0": "OLED显示生效",
      "category": Blockly.Categories.motion,
      "colour": "#24B0E0",
      "extensions": ["shape_statement"]
    });
  }
};
Blockly.Blocks['motion_dsx_oled_showstr'] = {
  
  init: function() {
    this.jsonInit({
      "message0": "在OLED坐标 X %1 Y %2  显示字符串 %3 颜色 %4",
      "args0": [
          {
              "type": "input_value",
              "name": "ROW",
          },
          {
              "type": "input_value",
              "name": "COL"
          },
          {
              "type": "input_value",
              "name": "STRING"
          },{
            "type": "field_dropdown",
            "name": "COLOR",
            "options": [
              ['黑底白字', '1'],
              ['白底黑字', '0'],
            ]
        }
      ],
      "category": Blockly.Categories.motion,
      "colour": "#24B0E0",
      "extensions": ["shape_statement"]
    });
  }
};
Blockly.Blocks['motion_dsx_oled_fillline'] = {
  
  init: function() {
    this.jsonInit({
      "message0": "在OLED擦除 第 %1 行 颜色 %2",
      "args0": [
        {
            "type": "field_dropdown",
            "name": "ROW",
            "options": [
                ['1', '1'],
                ['2', '2'],
                ['3', '3'],
                ['4', '4'],
                ['5', '5'],
            ]
        },{
            "type": "field_dropdown",
            "name": "COLOR",
            "options": [
                ['黑底', '0'],
                ['白底', '1'],
            ]
        }
      ],
      "category": Blockly.Categories.motion,
      "colour": "#24B0E0",
      "extensions": ["shape_statement"]
    });
  }
};
Blockly.Blocks['motion_dsx_oled_showstr2'] = {
  
  init: function() {
    this.jsonInit({
      "message0": "在OLED 第 %1 行显示字符串 %2 颜色 %3",
      "args0": [
          {
              "type": "field_dropdown",
              "name": "ROW",
              "options": [
                  ['1', '1'],
                  ['2', '2'],
                  ['3', '3'],
                  ['4', '4'],
                  ['5', '5'],
              ]
          },
          {
              "type": "input_value",
              "name": "STRING"
          },{
            "type": "field_dropdown",
            "name": "COLOR",
            "options": [
                ['黑底白字', '1'],
                ['白底黑字', '0'],
            ]
        }
      ],
      "category": Blockly.Categories.motion,
      "colour": "#24B0E0",
      "extensions": ["shape_statement"]
    });
  }
};
Blockly.Blocks['motion_dsx_oled_clear'] = {
  init: function() {
    this.jsonInit({
      "message0": "OLED显示 %1",
      "args0":[
          {
              "type": "field_dropdown",
              "name": "VALUE",
              "options": [
                ["清空", '0'],
                ["全亮", '1'],
              ]
          }
      ],
      "colour": "#24B0E0",
      "category": Blockly.Categories.motion,
      "extensions": ["shape_statement"]
    });
  }
};
Blockly.Blocks['motion_dsx_oled_pixel'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "描点 x %1 y %2 状态 %3",
        "args0":[
            {
                "type": "input_value",
                "name": "X"
            },{
                "type": "input_value",
                "name": "Y"
            },{
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                  ["亮", '1'],
                  ["暗", '0']
                ]
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_oled_progress'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "进度条 x %1 y %2 宽 %3 高 %4 进度 %5",
        "args0":[
            {
                "type": "input_value",
                "name": "X"
            },{
                "type": "input_value",
                "name": "Y"
            },{
                "type": "input_value",
                "name": "W"
            },{
                "type": "input_value",
                "name": "H"
            },{
                "type": "input_value",
                "name": "PROGRESS"
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_oled_histogram'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "柱状条 %1 x %2 y %3 宽 %4 高 %5 进度 %6",
        "args0":[
            {
                "type": "field_dropdown",
                "name": "DIRECTION",
                "options": [
                  ["垂直", '1'],
                  ["水平", '0']
                ]
            },
            {
                "type": "input_value",
                "name": "X"
            },{
                "type": "input_value",
                "name": "Y"
            },{
                "type": "input_value",
                "name": "W"
            },{
                "type": "input_value",
                "name": "H"
            },{
                "type": "input_value",
                "name": "PROGRESS"
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_oled_line'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "%1 %2 线 x %3 y %4 长度 %5",
        "args0":[
            {
                "type": "field_dropdown",
                "name": "MODE",
                "options": [
                  ["绘制", '1'],
                  ["擦除", '0']
                ]
            },
            {
                "type": "field_dropdown",
                "name": "DIRECTION",
                "options": [
                  ["垂直", '0'],
                  ["水平", '1']
                ]
            },
            {
                "type": "input_value",
                "name": "X"
            },{
                "type": "input_value",
                "name": "Y"
            },{
                "type": "input_value",
                "name": "LENGTH"
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_oled_line2'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "%1 线 x1 %2 y1 %3 到 x2 %4 y2 %5",
        "args0":[
            {
                "type": "field_dropdown",
                "name": "MODE",
                "options": [
                  ["绘制", '1'],
                  ["擦除", '0']
                ]
            },
            {
                "type": "input_value",
                "name": "X1"
            },{
                "type": "input_value",
                "name": "Y1"
            },{
                "type": "input_value",
                "name": "X2"
            },{
                "type": "input_value",
                "name": "Y2"
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_oled_rect'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "%1 %2 矩形 x %3 y %4 宽 %5 高 %6",
        "args0":[
            {
                "type": "field_dropdown",
                "name": "MODE1",
                "options": [
                  ["绘制", '1'],
                  ["擦除", '0']
                ]
            },
            {
                "type": "field_dropdown",
                "name": "MODE2",
                "options": [
                  ["空心", '0'],
                  ["实心", '1']
                ]
            },
            {
                "type": "input_value",
                "name": "X"
            },{
                "type": "input_value",
                "name": "Y"
            },{
                "type": "input_value",
                "name": "W"
            },{
                "type": "input_value",
                "name": "H"
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_oled_boarder'] = {
    init: function() {
      this.jsonInit({
        "message0": "%1 弧角边框 x %2 y %3 宽 %4 高 %5 半径 %6",
        "args0":[
            {
                "type": "field_dropdown",
                "name": "MODE",
                "options": [
                  ["绘制", '1'],
                  ["擦除", '0']
                ]
            },
            {
                "type": "input_value",
                "name": "X"
            },
            {
                "type": "input_value",
                "name": "Y"
            },{
                "type": "input_value",
                "name": "W"
            },{
                "type": "input_value",
                "name": "H"
            },{
                "type": "input_value",
                "name": "R"
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_oled_circle'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "%1 %2 圆 x %3 y %4 半径 %5",
        "args0":[
            {
                "type": "field_dropdown",
                "name": "MODE1",
                "options": [
                  ["绘制", '1'],
                  ["擦除", '0']
                ]
            },{
                "type": "field_dropdown",
                "name": "MODE2",
                "options": [
                  ["空心", '0'],
                  ["实心", '1']
                ]
            },{
                "type": "input_value",
                "name": "X"
            },{
                "type": "input_value",
                "name": "Y"
            },{
                "type": "input_value",
                "name": "R"
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_oled_ellipse'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "%1 %2 椭圆 x %3 y %4 rx %5 ry %6",
        "args0":[
            {
                "type": "field_dropdown",
                "name": "MODE1",
                "options": [
                  ["绘制", '1'],
                  ["擦除", '0']
                ]
            },{
                "type": "field_dropdown",
                "name": "MODE2",
                "options": [
                  ["空心", '0'],
                  ["实心", '1']
                ]
            },{
                "type": "input_value",
                "name": "X"
            },{
                "type": "input_value",
                "name": "Y"
            },{
                "type": "input_value",
                "name": "RX"
            },{
                "type": "input_value",
                "name": "RY"
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_oled_arc'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "%1 圆弧 x %2 y %3 半径 %4 起始角度 %5 结束角度 %6",
        "args0":[
            {
                "type": "field_dropdown",
                "name": "MODE1",
                "options": [
                  ["绘制", '1'],
                  ["擦除", '0']
                ]
            },{
                "type": "input_value",
                "name": "X"
            },{
                "type": "input_value",
                "name": "Y"
            },{
                "type": "input_value",
                "name": "R"
            },{
                "type": "input_value",
                "name": "ANGLE1"
            },{
                "type": "input_value",
                "name": "ANGLE2"
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_oled_triangle'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "%1 %2 三角 x1 %3 y1 %4 x2 %5 y2 %6 x3 %7 y3 %8",
        "args0":[
            {
                "type": "field_dropdown",
                "name": "MODE1",
                "options": [
                  ["绘制", '1'],
                  ["擦除", '0']
                ]
            },{
                "type": "field_dropdown",
                "name": "MODE2",
                "options": [
                  ["空心", '0'],
                  ["实心", '1']
                ]
            },{
                "type": "input_value",
                "name": "X1"
            },{
                "type": "input_value",
                "name": "Y1"
            },{
                "type": "input_value",
                "name": "X2"
            },{
                "type": "input_value",
                "name": "Y2"
            },{
                "type": "input_value",
                "name": "X3"
            },{
                "type": "input_value",
                "name": "Y3"
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_oled_pointer'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "%1 指针 x %2 y %3 半径 %4 角度 %5",
        "args0":[
            {
                "type": "field_dropdown",
                "name": "MODE1",
                "options": [
                  ["绘制", '1'],
                  ["擦除", '0']
                ]
            },{
                "type": "input_value",
                "name": "X"
            },{
                "type": "input_value",
                "name": "Y"
            },{
                "type": "input_value",
                "name": "R"
            },{
                "type": "input_value",
                "name": "ANGLE"
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_oled_scale'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "%1 弧形刻度 x %2 y %3 半径 %4 角度 %5 刻度长度 %6",
        "args0":[
            {
                "type": "field_dropdown",
                "name": "MODE1",
                "options": [
                  ["绘制", '1'],
                  ["擦除", '0']
                ]
            },{
                "type": "input_value",
                "name": "X"
            },{
                "type": "input_value",
                "name": "Y"
            },{
                "type": "input_value",
                "name": "R"
            },{
                "type": "input_value",
                "name": "ANGLE"
            },{
                "type": "input_value",
                "name": "SCALE"
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_oled_image2'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "在OLED拉伸显示图片 %1 ",
        "args0":[
            {
                "type": "field_dropdown",
                "name": "IMAGE",
                "options": function() {
                    if(window.image_list == undefined){
                      window.image_list = [["导入图片","import_image"]]
                    }
                    return window.image_list;
                },
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_oled_image'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "在OLED坐标 X %1 Y %2  绘制图片 %3",
        "args0":[
            {
                "type": "input_value",
                "name": "X",
            },
            {
                "type": "input_value",
                "name": "Y",
            },
            {
                "type": "field_dropdown",
                "name": "IMAGE",
                "options": function() {
                    if(window.image_list == undefined){
                      window.image_list = [["导入图片","import_image"]]
                    }
                    return window.image_list;
                },
            },
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_connect_wifi'] = {
  init: function() {
    this.jsonInit({
      "message0": "连接WiFi名 %1 密码 %2",
      "args0": [
        {
            "type": "input_value",
            "name": "SSID",
        },
        {
            "type": "input_value",
            "name": "PASSWORD"
        }
      ],
      "category": Blockly.Categories.motion,
      "colour": "#A828E5",
      "extensions": ["shape_statement"]
    });
  }
};

Blockly.Blocks['motion_dsx_isconnected'] = {
    init: function() {
      this.jsonInit({
        "message0": "Wi-Fi连接成功?",
        "category": Blockly.Categories.motion,
        "colour": "#A828E5",
        "extensions": ["output_boolean"]
      });
    }
  };
  Blockly.Blocks['motion_dsx_getip'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "本机IP地址",
        "category": Blockly.Categories.motion,
        "colour": "#A828E5",
        "extensions": ["output_number"]
      });
    }
  };
Blockly.Blocks['motion_dsx_disconnect_wifi'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "断开WiFi连接",
        "category": Blockly.Categories.motion,
        "colour": "#A828E5",
        "extensions": ["shape_statement"]
      });
    }
  };
Blockly.Blocks['motion_dsx_start_hotspot'] = {
  
  init: function() {
    this.jsonInit({
      "message0": "开启热点WiFi名 %1 密码 %2",
      "args0": [
        {
            "type": "input_value",
            "name": "SSID",
        },
        {
            "type": "input_value",
            "name": "PASSWORD"
        }
      ],
      "category": Blockly.Categories.motion,
      "colour": "#A828E5",
      "extensions": ["shape_statement"]
    });
  }
};
Blockly.Blocks['motion_dsx_config_hotspot'] = {
  
  init: function() {
    this.jsonInit({
      "message0": "设置热点IP %1 子网掩码 %2 网关 %3",
      "args0": [
        {
            "type": "input_value",
            "name": "IP",
        },
        {
            "type": "input_value",
            "name": "NETMASK"
        },
        {
            "type": "input_value",
            "name": "GATEWAY"
        }
      ],
      "category": Blockly.Categories.motion,
      "colour": "#A828E5",
      "extensions": ["shape_statement"]
    });
  }
};
Blockly.Blocks['motion_dsx_stop_hotspot'] = {
  
  init: function() {
    this.jsonInit({
      "message0": "关闭热点",
      "category": Blockly.Categories.motion,
      "colour": "#A828E5",
      "extensions": ["shape_statement"]
    });
  }
};
Blockly.Blocks['motion_dsx_socket_create'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "创建socket %1 地址 %2 类型 %3",
        "args0":[
            {
                "type": "input_value",
                "name": "NAME"
            },
            {
                "type": "field_dropdown",
                "name": "TYPE",
                "options": [
                  ["AF_INET", 'AF_INET'],
                  ["AF_INET6", 'AF_INET6'],
                ]
            },
            {
                "type": "field_dropdown",
                "name": "TYPE2",
                "options": [
                  ["SOCK_STREAM", 'SOCK_STREAM'],
                  ["SOCK_DGRAM", 'SOCK_DGRAM'],
                  ["SOCK_RAW", 'SOCK_RAW'],
                  ["SO_REUSEADDR", 'SO_REUSEADDR']
                ]
            }
        ],
        "category": Blockly.Categories.motion,
        "colour": "#FF6BD6",
        "extensions": ["shape_statement"]
      });
    }
};

Blockly.Blocks['motion_dsx_socket_close'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "socket %1 关闭",
        "args0":[
            {
                "type": "input_value",
                "name": "NAME"
            }
        ],
        "category": Blockly.Categories.motion,
        "colour": "#FF6BD6",
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_socket_bind'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "socket %1 绑定地址 %2 端口 %3",
        "args0":[
            {
                "type": "input_value",
                "name": "NAME"
            },
            {
                "type": "input_value",
                "name": "ADDR"
            },
            {
                "type": "input_value",
                "name": "PORT"
            }
        ],
        "category": Blockly.Categories.motion,
        "colour": "#FF6BD6",
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_socket_timeout'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "socket %1 设置超时 %2 秒",
        "args0":[
            {
                "type": "input_value",
                "name": "NAME"
            },
            {
                "type": "input_value",
                "name": "TIMEOUT"
            }
        ],
        "category": Blockly.Categories.motion,
        "colour": "#FF6BD6",
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_socket_listen'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "监听socket %1 backlog个数 %2",
        "args0":[
            {
                "type": "input_value",
                "name": "NAME"
            },
            {
                "type": "input_value",
                "name": "COUNT"
            }
        ],
        "category": Blockly.Categories.motion,
        "colour": "#FF6BD6",
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_socket_setbroadcast'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "设置socket %1 为广播类型",
        "args0":[
            {
                "type": "input_value",
                "name": "NAME"
            }
        ],
        "category": Blockly.Categories.motion,
        "colour": "#FF6BD6",
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_socket_connect'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "socket %1 连接host %2 端口 %3",
        "args0":[
            {
                "type": "input_value",
                "name": "NAME"
            },
            {
                "type": "input_value",
                "name": "HOST"
            },
            {
                "type": "input_value",
                "name": "PORT"
            }
        ],
        "category": Blockly.Categories.motion,
        "colour": "#FF6BD6",
        "extensions": ["output_boolean"]
      });
    }
};
Blockly.Blocks['motion_dsx_socket_accept'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "socket %1 接收链接请求并返回socket对象",
        "args0":[
            {
                "type": "input_value",
                "name": "NAME"
            }
        ],
        "category": Blockly.Categories.motion,
        "colour": "#FF6BD6",
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_dsx_socket_send'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "socket %1 发送字符  %2 ",
        "args0":[
            {
                "type": "input_value",
                "name": "NAME"
            },{
                "type": "input_value",
                "name": "CONTENT"
            }
        ],
        "category": Blockly.Categories.motion,
        "colour": "#FF6BD6",
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_socket_sendto'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "socket %1 发送UDP字符  %2 到IP地址 %3 端口 %4",
        "args0":[
            {
                "type": "input_value",
                "name": "NAME"
            },{
                "type": "input_value",
                "name": "CONTENT"
            },{
                "type": "input_value",
                "name": "ADDR"
            },{
                "type": "input_value",
                "name": "PORT"
            }
        ],
        "category": Blockly.Categories.motion,
        "colour": "#FF6BD6",
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_socket_recv'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "socket %1 接收字符数据",
        "args0":[
            {
                "type": "input_value",
                "name": "NAME"
            }
        ],
        "category": Blockly.Categories.motion,
        "colour": "#FF6BD6",
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_dsx_socket_recvfrom'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "socket %1 接收UDP字符数据 长度 %2",
        "args0":[
            {
                "type": "input_value",
                "name": "NAME"
            },{
                "type": "input_value",
                "name": "LENGTH"
            }
        ],
        "category": Blockly.Categories.motion,
        "colour": "#FF6BD6",
        "extensions": ["output_number"]
      });
    }
};

Blockly.Blocks['motion_dsx_conn_create_server'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "将大师兄设为服务器 端口 %1 最大连接数 %2",
        "args0":[
            {
                "type": "input_value",
                "name": "PORT"
            },
            {
                "type": "input_value",
                "name": "COUNT"
            }
        ],
        "category": Blockly.Categories.motion,
        "colour": "#2CCAAD",
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_conn_create_client'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "将大师兄设为客户端",
        "category": Blockly.Categories.motion,
        "colour": "#2CCAAD",
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_conn_connect'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "连接到服务器地址 %1 端口 %2",
        "args0":[
            {
                "type": "input_value",
                "name": "HOST"
            },
            {
                "type": "input_value",
                "name": "PORT"
            }
        ],
        "category": Blockly.Categories.motion,
        "colour": "#2CCAAD",
        "extensions": ["output_boolean"]
      });
    }
};
Blockly.Blocks['motion_dsx_conn_accept'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "将 %1 设置为服务器接收到的连接",
        "args0":[
            {
                "type": "field_dropdown",
                "name": "SOCKET",
                "options": function() {
                    if(window.conn_list == undefined){
                        window.conn_list = [["dsx_client","dsx_client"],["新建连接名","new_client"]]
                    }
                    return window.conn_list;
                },
            },
        ],
        "category": Blockly.Categories.motion,
        "colour": "#2CCAAD",
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_conn_hasconn'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "接收到新连接",
        "category": Blockly.Categories.motion,
        "colour": "#2CCAAD",
        "extensions": ["output_boolean"]
      });
    }
};
Blockly.Blocks['motion_dsx_conn_getconn'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "获取新连接",
        "category": Blockly.Categories.motion,
        "colour": "#2CCAAD",
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_dsx_conn_client_recv'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "客户端接收通信数据",
        "category": Blockly.Categories.motion,
        "colour": "#2CCAAD",
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_dsx_conn_client_send'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "客户端发送通信数据 %1",
        "args0":[
            {
                "type": "input_value",
                "name": "CONTENT"
            },
        ],
        "category": Blockly.Categories.motion,
        "colour": "#2CCAAD",
        "extensions": ["shape_statement"]
      });
    }
};

Blockly.Blocks['motion_dsx_conn_recv'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "服务器从 %1 接收通信数据",
        "args0":[
            {
                "type": "input_value",
                "name": "SOCKET"
            },
        ],
        "category": Blockly.Categories.motion,
        "colour": "#2CCAAD",
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_dsx_conn_send'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "服务器发送通信数据 %1 到 %2",
        "args0":[
            {
                "type": "input_value",
                "name": "CONTENT"
            },
            {
                "type": "input_value",
                "name": "SOCKET"
            },
        ],
        "category": Blockly.Categories.motion,
        "colour": "#2CCAAD",
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_conn_close_server'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "关闭服务器",
        "category": Blockly.Categories.motion,
        "colour": "#2CCAAD",
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_conn_close_client'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "关闭客户端",
        "category": Blockly.Categories.motion,
        "colour": "#2CCAAD",
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_digital_pin'] = {
    
    init: function() {
      this.jsonInit({
        "message0": Blockly.Msg.MOTION_DIGITAL_PIN,
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P5", '5'],
                    ["P8", '8'],
                    ["P11", '11'],
                    ["P12", '12'],
                    ["P13", '13'],
                    ["P14", '14'],
                    ["P15", '15'],
                ]
            },
            {
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                  [Blockly.Msg.MOTION_PIN_HIGH, '1'],
                  [Blockly.Msg.MOTION_PIN_LOW, '0']
                ]
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["output_boolean"]
      });
    }
};
Blockly.Blocks['motion_dsx_analog_pin'] = {
    
    init: function() {
      this.jsonInit({
        "message0": Blockly.Msg.MOTION_ANALOG_PIN,
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P13", '13'],
                    ["P14", '14'],
                ]
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_dsx_set_digital_pin'] = {
    
    init: function() {
      this.jsonInit({
        "message0": Blockly.Msg.MOTION_SET_DIGITAL_PIN,
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P5", '5'],
                    ["P8", '8'],
                    ["P11", '11'],
                    ["P12", '12'],
                    ["P13", '13'],
                    ["P14", '14'],
                    ["P15", '15'],
                ]
            },
            {
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                  [Blockly.Msg.MOTION_PIN_HIGH, '1'],
                  [Blockly.Msg.MOTION_PIN_LOW, '0']
                ]
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_set_analog_pin_freq'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "设置引脚 %1 PWM频率 %2",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P5", '5'],
                    ["P8", '8'],
                    ["P11", '11'],
                    ["P12", '12'],
                    ["P13", '13'],
                    ["P14", '14'],
                    ["P15", '15'],
                ]
            },
            {
                "type": "input_value",
                "name": "FREQ"
            },
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_set_analog_pin_duty'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "设置引脚 %1 PWM占空比 %2",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P5", '5'],
                    ["P8", '8'],
                    ["P11", '11'],
                    ["P12", '12'],
                    ["P13", '13'],
                    ["P14", '14'],
                    ["P15", '15'],
                ]
            },
            {
                "type": "input_value",
                "name": "DUTY"
            },
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};

Blockly.Blocks['motion_dsx_unisound'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "获取云知声数据",
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_dsx_unisound_value'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "%1",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "INDEX",
                "options": [
                  ["你好,大师兄", '5'],
                  ["请开灯", '1'],
                  ["请关灯", '2'],
                  ["调亮一点", '3'],
                  ["调暗一点", '4'],
                  ["开门", '6'],
                  ["关门", '7'],
                  ["左转",'8'],
                  ["右转",'9'],
                  ["前进",'10'],
                  ["后退",'11'],
                  ["停止",'12'],
                  ["浇水",'13'],
                  ['打开风扇','14'],
                  ['关闭风扇','15'],
                  ['播放','16'],
                  ['开始','17'],
                  ['结束','18'],
                  ['报警','19'],
                  ['聪明','20'],
                  ['温度','21'],
                  ['湿度','22'],
                  ['时间','23'],
                  ['天气','24'],
                  ['多少岁','25'],
                  ['你是谁','26'],
                  ['难过','27'],
                  ['开心','28'],
                  ['歌曲','29'],
                  ['太热了','30'],
                  ['好暗','31'],
                  ['打开水泵','32'],
                  ['关闭水泵','33'],
                  ['开窗','34'],
                  ['关窗','35'],
                  ["打开报警", '36'],
                  ["关闭报警", '37'],
                ]
            },
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_dsx_init_uart'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "初始化串口 %1 波特率 %2",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "INDEX",
                "options": [
                  ["uart", '1'],
                ]
            },
            {
                "type": "field_dropdown",
                "name": "BAUD",
                "options": [
                    ['115200', '115200'],
                    ['57600', '57600'],
                    ['56000', '56000'],
                    ['43000', '43000'],
                    ['38400', '38400'],
                    ['31250', '31250'],
                    ['28800', '28800'],
                    ['19200', '19200'],
                    ['14400', '14400'],
                    ['9600', '9600'],
                    ['4800', '4800'],
                    ['2400', '2400'],
                    ['1200', '1200'],
                    ['600', '600'],
                    ['300', '300'],
                ]
            },
        ],        
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_close_uart'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "关闭串口 %1",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "INDEX",
                "options": [
                  ["uart", '1'],
                ]
            },
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_uart_isinit'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "串口 %1 已初始化",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "INDEX",
                "options": [
                  ["uart", '1'],
                ]
            },
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["output_boolean"]
      });
    }
};
Blockly.Blocks['motion_dsx_uart_write'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "串口 %1 发送文本 %2 %3",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "INDEX",
                "options": [
                  ["uart", '1'],
                ]
            },
            {
                "type": "input_value",
                "name": "VALUE"
            },
            {
                "type": "field_dropdown",
                "name": "ENDS",
                "options": [
                  ["换行", 'n'],
                  ["不换行", ''],
                ]
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_uart_write2'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "串口 %1 发送字节数据 %2",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "INDEX",
                "options": [
                  ["uart", '1'],
                ]
            },
            {
                "type": "input_value",
                "name": "VALUE"
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_uart_read'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "读取串口 %1 长度 %2 字节数据",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "INDEX",
                "options": [
                  ["uart", '1'],
                ]
            },
            {
                "type": "input_value",
                "name": "VALUE"
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["output_string"]
      });
    }
};
Blockly.Blocks['motion_dsx_uart_readline'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "读取串口 %1 一行数据数据",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "INDEX",
                "options": [
                  ["uart", '1'],
                ]
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["output_string"]
      });
    }
};
Blockly.Blocks['motion_dsx_uart_canread'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "串口 %1 缓存数据大小",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "INDEX",
                "options": [
                  ["uart", '1'],
                ]
            },
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_dsx_init_i2c'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "初始化I2C 频率 %1",
        "args0": [
            {
                "type": "input_value",
                "name": "FREQ"
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_close_i2c'] = {
    
    init: function() {
      this.jsonInit({
        "message0": "关闭I2C %1",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "INDEX",
                "options": [
                  ["1", '1'],
                  ["2", '2'],
                ]
            },
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_i2c_write'] = {
    init: function() {
      this.jsonInit({
        "message0": "I2C 地址 %1 写入 %2",
        "args0": [
            {
                "type": "input_value",
                "name": "ADDR"
            },
            {
                "type": "input_value",
                "name": "VALUE"
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_dsx_i2c_read'] = {
    init: function() {
      this.jsonInit({
        "message0": "读取I2C 地址 %1 数据 长度 %2 字节",
        "args0": [
            {
                "type": "input_value",
                "name": "ADDR"
            },
            {
                "type": "input_value",
                "name": "LEN"
            }
        ],
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_dsx_i2c_scan'] = {
    init: function() {
      this.jsonInit({
        "message0": "I2C扫描结果",
        "colour": "#24B0E0",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_dsx_playmusic2'] = {
  init: function() {
    this.jsonInit({
      "message0": "%1 播放音乐 乐谱 %2 ",
      "args0": [
          
        {
            "type": "field_dropdown",
            "name": "TYPE",
            "options": [
              ["后台", '0'],
              ["前台", '1'],
            ]
        },
        {
            "type": "input_value",
            "name": "MUSIC"
        }
      ],
      "category": Blockly.Categories.motion,
      "extensions": ["colours_motion", "shape_statement"]
    });
  }
};
Blockly.Blocks['motion_dsx_playmusic'] = {
  /**
   * Block to report X.
   * @this Blockly.Block
   */
  init: function() {
    this.jsonInit({
      "message0": "%1 播放音乐 %2",
      "args0": [
            {
                "type": "field_dropdown",
                "name": "TYPE",
                "options": [
                  ["后台", '0'],
                  ["前台", '1'],
                ]
            },
            {
                "type": "field_dropdown",
                "name": "MUSIC",
                "options": function() {
                    if(window.music_list == undefined){
                      window.music_list = [["导入音乐","import_music"]]
                    }
                    return window.music_list;
                },
            },
      ],
      "category": Blockly.Categories.motion,
      "colour": "#24B0E0",
      "extensions": ["shape_statement"]
    });
  }
};
Blockly.Blocks['motion_dsx_stopmusic'] = {
  init: function() {
    this.jsonInit({
      "message0": "停止播放音乐",
      "category": Blockly.Categories.motion,
      "colour": "#24B0E0",
      "extensions": ["shape_statement"]
    });
  }
};
Blockly.Blocks['motion_hw_set_motor'] = {
        /**
         * Block to move steps.
         * @this Blockly.Block
         */
        init: function() {
          this.jsonInit({
            "message0": "设置电机 %1 速度为 %2 %3",
            "args0": [
                {
                    "type": "field_dropdown",
                    "name": "MOTOR_INDEX",
                    "options": [
                      [Blockly.Msg.MOTION_MOTOR_1, '1'],
                      [Blockly.Msg.MOTION_MOTOR_2, '2'],
                      ['M3', '3'],
                      ['M4', '4'],
                      [Blockly.Msg.MOTION_MOTOR_ALL, '0'],
                    ]
                },
                {
                    "type": "input_value",
                    "name": "SPEED"
                },
                {
                    "type": "field_dropdown",
                    "name": "DIRECTION",
                    "options": [
                      [Blockly.Msg.MOTION_MOTOR_FORWARD, '0'],
                      [Blockly.Msg.MOTION_MOTOR_REVERSE, '1']
                    ]
                }
            ],
            "colour": "#9999CC",
            "category": Blockly.Categories.motion,
            "extensions": ["shape_statement"]
          });
        }
    };
    Blockly.Blocks['motion_hw_get_motor'] = {
          /**
           * Block to move steps.
           * @this Blockly.Block
           */
          init: function() {
            this.jsonInit({
              "message0": "获取电机 %1 速度",
              "args0": [
                  {
                      "type": "field_dropdown",
                      "name": "MOTOR_INDEX",
                      "options": [
                        [Blockly.Msg.MOTION_MOTOR_1, '1'],
                        [Blockly.Msg.MOTION_MOTOR_2, '2'],
                        ['M3', '3'],
                        ['M4', '4'],
                      ]
                  }
              ],
              "colour": "#9999CC",
              "category": Blockly.Categories.motion,
              "extensions": ["output_number"]
            });
          }
      };
  Blockly.Blocks['motion_hw_stop_motor'] = {
      /**
       * Block to move steps.
       * @this Blockly.Block
       */
      init: function() {
        this.jsonInit({
          "message0": "停止电机 %1",
          "args0": [
              {
                  "type": "field_dropdown",
                  "name": "MOTOR_INDEX",
                  "options": [
                    [Blockly.Msg.MOTION_MOTOR_1, '1'],
                    [Blockly.Msg.MOTION_MOTOR_2, '2'],
                    ['M3', '3'],
                    ['M4', '4'],
                    [Blockly.Msg.MOTION_MOTOR_ALL, '0'],
                  ]
              }
          ],
          "colour": "#9999CC",
          "category": Blockly.Categories.motion,
          "extensions": ["shape_statement"]
        });
      }
    };
    Blockly.Blocks['motion_hw_set_servo'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "设置舵机 %1 角度为 %2",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["S1", '1'],
                    ["S2", '2'],
                    ["S3", '3'],
                    ["S4", '4'],
                    ["全部", '0'],
                ]
            },
            {
                "type": "input_value",
                "name": "ANGLE"
            },
        ],
        "category": Blockly.Categories.motion,
        "colour": "#9999CC",
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_hw_set_light'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "%1 小灯",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                    ["打开", '1'],
                    ["关闭", '0'],
                ]
            }
        ],
        "colour": "#9999CC",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
  Blockly.Blocks['motion_pz_set_motor'] = {
        /**
         * Block to move steps.
         * @this Blockly.Block
         */
        init: function() {
          this.jsonInit({
            "message0": "设置电机 %1 速度为 %2 %3",
            "args0": [
                {
                    "type": "field_dropdown",
                    "name": "MOTOR_INDEX",
                    "options": [
                      [Blockly.Msg.MOTION_MOTOR_1, '0'],
                      [Blockly.Msg.MOTION_MOTOR_2, '1'],
                      [Blockly.Msg.MOTION_MOTOR_ALL, '2'],
                    ]
                },
                {
                    "type": "input_value",
                    "name": "SPEED"
                },
                {
                    "type": "field_dropdown",
                    "name": "DIRECTION",
                    "options": [
                      [Blockly.Msg.MOTION_MOTOR_FORWARD, '0'],
                      [Blockly.Msg.MOTION_MOTOR_REVERSE, '1']
                    ]
                }
            ],
            "colour": "#D2691E",
            "category": Blockly.Categories.motion,
            "extensions": ["shape_statement"]
          });
        }
    };
  Blockly.Blocks['motion_pz_stop_motor'] = {
      /**
       * Block to move steps.
       * @this Blockly.Block
       */
      init: function() {
        this.jsonInit({
          "message0": "停止电机 %1",
          "args0": [
              {
                  "type": "field_dropdown",
                  "name": "MOTOR_INDEX",
                  "options": [
                    [Blockly.Msg.MOTION_MOTOR_1, '0'],
                    [Blockly.Msg.MOTION_MOTOR_2, '1'],
                    [Blockly.Msg.MOTION_MOTOR_ALL, '2'],
                  ]
              }
          ],
          "colour": "#D2691E",
          "category": Blockly.Categories.motion,
          "extensions": ["shape_statement"]
        });
      }
    };
Blockly.Blocks['motion_pz_set_servo'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "设置舵机 %1 角度为 %2",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["S1", '3'],
                    ["S2", '4'],
                    ["S3", '5'],
                    ["S4", '6'],
                    ["全部", '7'],
                ]
            },
            {
                "type": "input_value",
                "name": "ANGLE"
            },
        ],
        "category": Blockly.Categories.motion,
        "colour": "#D2691E",
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_pz_set_light'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "%1 小灯",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                    ["打开", '1'],
                    ["关闭", '0'],
                ]
            }
        ],
        "colour": "#D2691E",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_set_servo'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": Blockly.Msg.MOTION_SET_SERVO,
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P5", '5'],
                    ["P8", '8'],
                    ["P11", '11'],
                    ["P12", '12'],
                    ["P13", '13'],
                    ["P14", '14'],
                    ["P15", '15'],
                ]
            },
            {
                "type": "input_value",
                "name": "ANGLE"
            },
        ],
        "category": Blockly.Categories.motion,
        "colour": "#ff00ff",
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_set_motor'] = {
      /**
       * Block to move steps.
       * @this Blockly.Block
       */
      init: function() {
        this.jsonInit({
          "message0": Blockly.Msg.MOTION_SET_MOTOR,
          "args0": [
              {
                  "type": "field_dropdown",
                  "name": "MOTOR_INDEX",
                  "options": [
                    [Blockly.Msg.MOTION_MOTOR_1, '0'],
                    [Blockly.Msg.MOTION_MOTOR_2, '1'],
                    [Blockly.Msg.MOTION_MOTOR_ALL, '2'],
                  ]
              },
              {
                  "type": "input_value",
                  "name": "SPEED"
              },
              {
                  "type": "field_dropdown",
                  "name": "DIRECTION",
                  "options": [
                    [Blockly.Msg.MOTION_MOTOR_FORWARD, '0'],
                    [Blockly.Msg.MOTION_MOTOR_REVERSE, '1']
                  ]
              }
          ],
          "colour": "#9966FF",
          "category": Blockly.Categories.motion,
          "extensions": ["shape_statement"]
        });
      }
  };
Blockly.Blocks['motion_stop_motor'] = {
    /**
     * Block to move steps.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": Blockly.Msg.MOTION_STOP_MOTOR,
        "args0": [
            {
                "type": "field_dropdown",
                "name": "MOTOR_INDEX",
                "options": [
                  [Blockly.Msg.MOTION_MOTOR_1, '0'],
                  [Blockly.Msg.MOTION_MOTOR_2, '1'],
                  [Blockly.Msg.MOTION_MOTOR_ALL, '2'],
                ]
            }
        ],
        "colour": "#9966FF",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
  };
Blockly.Blocks['motion_carrobot_get_sonic'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "读取超声波距离",
        "colour": "#CDAD00",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_carrobot_set_motor'] = {
    /**
     * Block to move steps.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": Blockly.Msg.MOTION_SET_MOTOR,
        "args0": [
            {
                "type": "field_dropdown",
                "name": "MOTOR_INDEX",
                "options": [
                  [Blockly.Msg.MOTION_MOTOR_1, '0'],
                  [Blockly.Msg.MOTION_MOTOR_2, '1'],
                  [Blockly.Msg.MOTION_MOTOR_ALL, '2'],
                ]
            },
            {
                "type": "input_value",
                "name": "SPEED"
            },
            {
                "type": "field_dropdown",
                "name": "DIRECTION",
                "options": [
                  [Blockly.Msg.MOTION_MOTOR_FORWARD, '0'],
                  [Blockly.Msg.MOTION_MOTOR_REVERSE, '1']
                ]
            }
        ],
        "colour": "#CDAD00",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_carrobot_stop_motor'] = {
  /**
   * Block to move steps.
   * @this Blockly.Block
   */
  init: function() {
    this.jsonInit({
      "message0": Blockly.Msg.MOTION_STOP_MOTOR,
      "args0": [
          {
              "type": "field_dropdown",
              "name": "MOTOR_INDEX",
              "options": [
                [Blockly.Msg.MOTION_MOTOR_1, '0'],
                [Blockly.Msg.MOTION_MOTOR_2, '1'],
                [Blockly.Msg.MOTION_MOTOR_ALL, '2'],
              ]
          }
      ],
      "colour": "#CDAD00",
      "category": Blockly.Categories.motion,
      "extensions": ["shape_statement"]
    });
  }
};
Blockly.Blocks['motion_carrobot_set_light'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "%1 %2 小灯",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                    ["打开", '1'],
                    ["关闭", '0'],
                ]
            },
            {
                "type": "field_dropdown",
                "name": "INDEX",
                "options": [
                    ["左边", '2'],
                    ["右边", '15'],
                ]
            }
        ],
        "colour": "#CDAD00",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_carrobot_get_tracked_init'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "初始化红外传感器 检测到轨迹为 %1",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                    ["高电平", '1'],
                    ["低电平", '0'],
                ]
            }
        ],
        "colour": "#CDAD00",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_carrobot_get_tracked'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": " %1 红外传感器检测到轨迹",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["左边", '8'],
                    ["右边", '11'],
                ]
            }
        ],
        "colour": "#CDAD00",
        "category": Blockly.Categories.motion,
        "extensions": ["output_boolean"]
      });
    }
};
Blockly.Blocks['motion_edu_get_sonic'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "读取超声波距离",
        "colour": "#EED8AE",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_edu_get_pm25'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "读取PM2.5",
        "colour": "#EED8AE",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_edu_get_blocked2'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "获取红外避障传感器数值",
        "colour": "#EED8AE",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_edu_get_key'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "开关被 %1",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                  ['按下', '0'],
                  ['释放', '1'],
                ]
            }
        ],
        "colour": "#EED8AE",
        "category": Blockly.Categories.motion,
        "extensions": ["output_boolean"]
      });
    }
};
Blockly.Blocks['motion_edu_fan'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "风扇 %1",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                    ['正转', '0'],
                    ['反转', '1'],
                ]
            }
        ],
        "colour": "#EED8AE",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_edu_pump'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "水泵 %1",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                  ['正转', '0'],
                  ['反转', '1'],
                ]
            }
        ],
        "colour": "#EED8AE",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_edu_set_light'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "%1 小灯",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                    ["打开", '1'],
                    ["关闭", '0'],
                ]
            }
        ],
        "colour": "#EED8AE",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_edu_get_soil'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "土壤湿度传感器数值",
        "colour": "#EED8AE",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_edu_get_light'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "获取光敏传感器数值",
        "colour": "#EED8AE",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_edu_get_flame2'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "火焰传感器数值",
        "colour": "#EED8AE",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_edu_get_smoke2'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "烟雾传感器数值",
        "colour": "#EED8AE",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
  Blockly.Blocks['motion_edu_matrix_key_init'] = {
      /**
       * Block to move steps.
       * @this Blockly.Block
       */
      init: function() {
        this.jsonInit({
            "message0": "初始化矩阵键盘被按下为 %1",
            "args0": [
              {
                  "type": "field_dropdown",
                  "name": "STATE",
                  "options": [
                      ["高电平", '1'],
                      ["低电平", '0'],
                  ]
              }
            ],
          "category": Blockly.Categories.motion,
          "colour": "#EED8AE",
          "extensions": ["shape_statement"]
        });
      }
    };
  Blockly.Blocks['motion_edu_matrix_key'] = {
      /**
       * Block to move steps.
       * @this Blockly.Block
       */
      init: function() {
        this.jsonInit({
            "message0": "矩阵键盘 %1 被 %2 ?",
            "args0": [
              {
                  "type": "field_dropdown",
                  "name": "INDEX",
                  "options": [
                      ['按键1', '0b0000000000000001'],
                      ['按键2', '0b0000000000000010'],
                      ['按键3', '0b0000000000000100'],
                      ['按键A', '0b0000000000001000'],
                      ['按键4', '0b0000000000010000'],
                      ['按键5', '0b0000000000100000'],
                      ['按键6', '0b0000000001000000'],
                      ['按键B', '0b0000000010000000'],
                      ['按键7', '0b0000000100000000'],
                      ['按键8', '0b0000001000000000'],
                      ['按键9', '0b0000010000000000'],
                      ['按键C', '0b0000100000000000'],
                      ['按键*', '0b0001000000000000'],
                      ['按键0', '0b0010000000000000'],
                      ['按键#', '0b0100000000000000'],
                      ['按键D', '0b1000000000000000'],
                      ['无任何按键', '0b0000000000000000'],
                  ]
              },{
                  "type": "field_dropdown",
                  "name": "STATE",
                  "options": [
                    ['按下', '0'],
                    ['释放', '1'],
                  ]
              }
            ],
          "category": Blockly.Categories.motion,
          "colour": "#EED8AE",
          "extensions": ["output_boolean"]
        });
      }
    };
Blockly.Blocks['motion_edu_dht_temperature'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "读取 DHT11温度",
        "colour": "#EED8AE",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_edu_dht_humidity'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "读取 DHT11湿度",
        "colour": "#EED8AE",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_edu_set_servo'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "设置舵机角度为 %1",
        "args0": [
            {
                "type": "input_value",
                "name": "ANGLE"
            },
        ],
        "category": Blockly.Categories.motion,
        "colour": "#EED8AE",
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_get_sonic'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "读取超声波距离 trig为 %1 echo 为 %2",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN1",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P5", '5'],
                    ["P8", '8'],
                    ["P11", '11'],
                    ["P12", '12'],
                    ["P13", '13'],
                    ["P14", '14'],
                    ["P15", '15'],
                ]
            },
            {
                "type": "field_dropdown",
                "name": "PIN2",
                "options": [
                    ["P2", '2'],
                    ["P1", '1'],
                    ["P5", '5'],
                    ["P8", '8'],
                    ["P11", '11'],
                    ["P12", '12'],
                    ["P13", '13'],
                    ["P14", '14'],
                    ["P15", '15'],
                ]
            }
        ],
        "colour": "#ff0000",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_dht_temperature'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "读取 DHT11 %1 温度",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P5", '5'],
                    ["P8", '8'],
                    ["P11", '11'],
                    ["P12", '12'],
                    ["P13", '13'],
                    ["P14", '14'],
                    ["P15", '15'],
                ]
            }
        ],
        "colour": "#c71585",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_dht_humidity'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "读取 DHT11 %1 湿度",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P5", '5'],
                    ["P8", '8'],
                    ["P11", '11'],
                    ["P12", '12'],
                    ["P13", '13'],
                    ["P14", '14'],
                    ["P15", '15'],
                ]
            }
        ],
        "colour": "#c71585",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_matrix_key_init'] = {
    /**
     * Block to move steps.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
          "message0": "初始化矩阵键盘被按下为 %1",
          "args0": [
            {
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                    ["高电平", '1'],
                    ["低电平", '0'],
                ]
            }
          ],
        "category": Blockly.Categories.motion,
        "colour": "#867892",
        "extensions": ["shape_statement"]
      });
    }
  };
Blockly.Blocks['motion_matrix_key'] = {
    /**
     * Block to move steps.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
          "message0": "矩阵键盘 SCL %1 SDO %2 %3 被 %4 ?",
          "args0": [
              
            {
                "type": "field_dropdown",
                "name": "SCL",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P5", '5'],
                    ["P8", '8'],
                    ["P11", '11'],
                    ["P12", '12'],
                    ["P13", '13'],
                    ["P14", '14'],
                    ["P15", '15'],
                ]
            },{
                "type": "field_dropdown",
                "name": "SDO",
                "options": [
                    ["P2", '2'],
                    ["P1", '1'],
                    ["P5", '5'],
                    ["P8", '8'],
                    ["P11", '11'],
                    ["P12", '12'],
                    ["P13", '13'],
                    ["P14", '14'],
                    ["P15", '15'],
                ]
            },
            {
                "type": "field_dropdown",
                "name": "INDEX",
                "options": [
                    ['按键1', '0b0000000000000001'],
                    ['按键2', '0b0000000000000010'],
                    ['按键3', '0b0000000000000100'],
                    ['按键A', '0b0000000000001000'],
                    ['按键4', '0b0000000000010000'],
                    ['按键5', '0b0000000000100000'],
                    ['按键6', '0b0000000001000000'],
                    ['按键B', '0b0000000010000000'],
                    ['按键7', '0b0000000100000000'],
                    ['按键8', '0b0000001000000000'],
                    ['按键9', '0b0000010000000000'],
                    ['按键C', '0b0000100000000000'],
                    ['按键*', '0b0001000000000000'],
                    ['按键0', '0b0010000000000000'],
                    ['按键#', '0b0100000000000000'],
                    ['按键D', '0b1000000000000000'],
                    ['无任何按键', '0b0000000000000000'],
                ]
            },{
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                  ['按下', '0'],
                  ['释放', '1'],
                ]
            }
          ],
        "category": Blockly.Categories.motion,
        "colour": "#867892",
        "extensions": ["output_boolean"]
      });
    }
  };
Blockly.Blocks['motion_get_pm25'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "读取PM2.5",
        "colour": "#ffbf00",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_get_soil'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "土壤湿度传感器 %1 数值",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P13", '13'],
                    ["P14", '14'],
                ]
            }
        ],
        "colour": "#808000",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_get_flame_init'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "初始化 火焰传感器检测到火焰为 %1",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                    ["高电平", '1'],
                    ["低电平", '0'],
                ]
            }
        ],
        "colour": "#2F4F4F",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_get_flame'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "火焰传感器 %1 检测到火焰",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P5", '5'],
                    ["P8", '8'],
                    ["P11", '11'],
                    ["P12", '12'],
                    ["P13", '13'],
                    ["P14", '14'],
                    ["P15", '15'],
                ]
            }
        ],
        "colour": "#2F4F4F",
        "category": Blockly.Categories.motion,
        "extensions": ["output_boolean"]
      });
    }
};
Blockly.Blocks['motion_get_flame2'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "火焰传感器 %1 数值",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P13", '13'],
                    ["P14", '14'],
                ]
            }
        ],
        "colour": "#2F4F4F",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_get_smoke_init'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "初始化烟雾传感器 检测到烟雾为 %1",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                    ["高电平", '1'],
                    ["低电平", '0'],
                ]
            }
        ],
        "colour": "#c71585",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_get_smoke'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "烟雾传感器 %1 检测到烟雾",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P5", '5'],
                    ["P8", '8'],
                    ["P11", '11'],
                    ["P12", '12'],
                    ["P13", '13'],
                    ["P14", '14'],
                    ["P15", '15'],
                ]
            }
        ],
        "colour": "#c71585",
        "category": Blockly.Categories.motion,
        "extensions": ["output_boolean"]
      });
    }
};
Blockly.Blocks['motion_get_smoke2'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "烟雾传感器 %1 数值",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P13", '13'],
                    ["P14", '14'],
                ]
            }
        ],
        "colour": "#c71585",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_get_infrared_init'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "初始化 红外热释电检测到障碍为 %1",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                    ["高电平", '1'],
                    ["低电平", '0'],
                ]
            }
        ],
        "colour": "#8B5742",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_get_infrared'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "红外热释电 %1 检测到障碍",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P5", '5'],
                    ["P8", '8'],
                    ["P11", '11'],
                    ["P12", '12'],
                    ["P13", '13'],
                    ["P14", '14'],
                    ["P15", '15'],
                ]
            }
        ],
        "colour": "#8B5742",
        "category": Blockly.Categories.motion,
        "extensions": ["output_boolean"]
      });
    }
};
Blockly.Blocks['motion_get_light'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "获取光敏传感器 %1 数值",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P13", '13'],
                    ["P14", '14'],
                ]
            }
        ],
        "colour": "#b7ff85",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_get_gray'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "获取灰度传感器 %1 数值",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P13", '13'],
                    ["P14", '14'],
                ]
            }
        ],
        "colour": "#a725ff",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_get_airpressure'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "获取气压传感器数值",
        "colour": "#975565",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_get_raindrop_init'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "初始化雨滴传感器 检测到雨滴为 %1",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                    ["高电平", '1'],
                    ["低电平", '0'],
                ]
            }
        ],
        "colour": "#ff4555",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_get_raindrop'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "雨滴传感器 %1 检测到雨滴",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P5", '5'],
                    ["P8", '8'],
                    ["P11", '11'],
                    ["P12", '12'],
                    ["P13", '13'],
                    ["P14", '14'],
                    ["P15", '15'],
                ]
            }
        ],
        "colour": "#ff4555",
        "category": Blockly.Categories.motion,
        "extensions": ["output_boolean"]
      });
    }
};
Blockly.Blocks['motion_get_raindrop2'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "获取雨滴传感器 %1 数值",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P13", '13'],
                    ["P14", '14'],
                ]
            }
        ],
        "colour": "#ff4555",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_get_blocked_init'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "初始化红外避障传感器 检测到障碍为 %1",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                    ["高电平", '1'],
                    ["低电平", '0'],
                ]
            }
        ],
        "colour": "#7755bb",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_get_blocked'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "红外避障传感器 %1 检测到障碍物",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P5", '5'],
                    ["P8", '8'],
                    ["P11", '11'],
                    ["P12", '12'],
                    ["P13", '13'],
                    ["P14", '14'],
                    ["P15", '15'],
                ]
            }
        ],
        "colour": "#7755bb",
        "category": Blockly.Categories.motion,
        "extensions": ["output_boolean"]
      });
    }
};
Blockly.Blocks['motion_get_blocked2'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "获取红外避障传感器 %1 数值",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P13", '13'],
                    ["P14", '14'],
                ]
            }
        ],
        "colour": "#7755bb",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_get_heartbeat'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "获取心率传感器数值",
        "colour": "#0055bb",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_get_tur_init'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "初始化浊度传感器 检测到浑浊为 %1",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                    ["高电平", '1'],
                    ["低电平", '0'],
                ]
            }
        ],
        "colour": "#77ddbb",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_get_tur'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "获取浊度传感器 %1 数值",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P13", '13'],
                    ["P14", '14'],
                ]
            }
        ],
        "colour": "#77ddbb",
        "category": Blockly.Categories.motion,
        "extensions": ["output_number"]
      });
    }
};
Blockly.Blocks['motion_get_tur2'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "浊度传感器 %1 检测到浑浊",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P5", '5'],
                    ["P8", '8'],
                    ["P11", '11'],
                    ["P12", '12'],
                    ["P13", '13'],
                    ["P14", '14'],
                    ["P15", '15'],
                ]
            }
        ],
        "colour": "#77ddbb",
        "category": Blockly.Categories.motion,
        "extensions": ["output_boolean"]
      });
    }
};
Blockly.Blocks['motion_set_light'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "%1 小灯 %2",
        "args0": [
            {
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                    ["打开", '1'],
                    ["关闭", '0'],
                ]
            },
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P5", '5'],
                    ["P8", '8'],
                    ["P11", '11'],
                    ["P12", '12'],
                    ["P13", '13'],
                    ["P14", '14'],
                    ["P15", '15'],
                ]
            }
        ],
        "colour": "#775500",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_mp3_set_vol'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "设置音量为 %1",
        "args0": [
            {
                "type": "input_value",
                "name": "VOL"
            }
        ],
        "colour": "#775555",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_mp3_play'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "播放",
        "colour": "#775555",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_mp3_pause'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "暂停播放",
        "colour": "#775555",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_mp3_stop'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "停止播放",
        "colour": "#775555",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_mp3_next'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "下一首曲目",
        "colour": "#775555",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_mp3_pre'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "上一首曲目",
        "colour": "#775555",
        "category": Blockly.Categories.motion,
        "extensions": ["shape_statement"]
      });
    }
};
Blockly.Blocks['motion_get_key'] = {
    /**
     * Block to report X.
     * @this Blockly.Block
     */
    init: function() {
      this.jsonInit({
        "message0": "按键 %1 被 %2",
        "args0": [
            
            {
                "type": "field_dropdown",
                "name": "PIN",
                "options": [
                    ["P1", '1'],
                    ["P2", '2'],
                    ["P5", '5'],
                    ["P8", '8'],
                    ["P11", '11'],
                    ["P12", '12'],
                    ["P13", '13'],
                    ["P14", '14'],
                    ["P15", '15'],
                ]
            },
            {
                "type": "field_dropdown",
                "name": "STATE",
                "options": [
                  ['按下', '0'],
                  ['释放', '1'],
                ]
            }
        ],
        "colour": "#00ddbb",
        "category": Blockly.Categories.motion,
        "extensions": ["output_boolean"]
      });
    }
};
Blockly.Python['motion_dsx_temperature'] = function(block) {
    return ["aht2x.temp()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_humi'] = function(block) {
    return ["aht2x.humi()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_get_light'] = function(block) {
    return ["ltr.get_light()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_beep_init'] = function(block) {
    return `machine.initBeep()\n`;
};
Blockly.Python['motion_dsx_beep_on'] = function(block) {
    return `beep.on()\n`;
};
Blockly.Python['motion_dsx_beep_off'] = function(block) {
    return `beep.off()\n`;
};
Blockly.Python['motion_dsx_playmusic'] = function(block) {
    var music = block.getFieldValue("MUSIC");
    var type = block.getFieldValue("TYPE");

    if(music.startsWith(`'`)&&music.endsWith(`'`)){
        music = music.slice(1,-1);
    }

    if(music == "default_music"){
        music = "0x15, 0x02, 0x16, 0x02, 0x17, 0x02, 0x15, 0x02, 0x15, 0x02,0x16, 0x02, 0x17, 0x02, 0x15, 0x02, 0x17, 0x02, 0x18, 0x02,0x19, 0x01, 0x17, 0x02, 0x18, 0x02, 0x19, 0x01, 0x19, 0x03,0x1A, 0x03, 0x19, 0x03, 0x18, 0x03, 0x17, 0x02, 0x15, 0x16,0x19, 0x03, 0x1A, 0x03, 0x19, 0x03, 0x18, 0x03, 0x17, 0x02,0x15, 0x16, 0x15, 0x02, 0x0F, 0x02, 0x15, 0x01, 0x15, 0x02,0x0F, 0x02, 0x15, 0x01, 0x00, 0x00";
    }
    return "beep.player(bytes(["+music+"])," + type + `)\n`;
};
Blockly.Python['motion_dsx_playmusic2'] = function(block) {
    var type = block.getFieldValue("TYPE");
    var music = Blockly.Python.valueToCode(block, 'MUSIC', Blockly.Python.ORDER_ATOMIC);

    if(music.startsWith(`'`)&&music.endsWith(`'`)){
        music = music.slice(1,-1);
    }
    return "machine.music_player(bytes(["+music+"])," + type + `)\n`;
};
Blockly.Python['motion_dsx_stopmusic'] = function(block) {
    return `beep.stop()\n`;
};
Blockly.Python['motion_dsx_init_key'] = function(block) {
    var index = block.getFieldValue("INDEX");
    return "machine.initKey(" + index + `)\n`;
};
Blockly.Python['motion_dsx_get_key'] = function(block) {
    var index = block.getFieldValue("INDEX");
    var state = block.getFieldValue("STATE");
    return ["(btn" + index + ".value() == " + state + ")", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_icm_init'] = function(block) {
    return `machine.icm_init()\n`;
};
Blockly.Python['motion_dsx_read_acc'] = function(block) {
    return ["imu.acc()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_read_gyro'] = function(block) {
    return ["imu.gyro()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_read_a'] = function(block) {
    var index = block.getFieldValue("INDEX");
    return ["imu.acc()[" + index +"]", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_read_g'] = function(block) {
    var index = block.getFieldValue("INDEX");
    return ["imu.gyro()[" + index +"]", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_read_angle'] = function(block) {
    var index = block.getFieldValue("INDEX");
    return ["imu.angle()[" + index +"]", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_oled_init'] = function(block) {
    return `oled.init()\n`;
};
Blockly.Python['motion_dsx_oled_flush'] = function(block) {
    return `oled.flush()\n`;
};
Blockly.Python['motion_dsx_oled_showstr'] = function(block) {
    var row = Blockly.Python.valueToCode(block, 'ROW', Blockly.Python.ORDER_ATOMIC);
    var col = Blockly.Python.valueToCode(block, 'COL', Blockly.Python.ORDER_ATOMIC);
    var string = Blockly.Python.valueToCode(block, 'STRING', Blockly.Python.ORDER_ATOMIC);
    var color = block.getFieldValue("COLOR");
    return "oled.show_str(" + "str(" + string + ")," + row +"," + col + "," + color + `,0)\n`;
};
Blockly.Python['motion_dsx_oled_showstr2'] = function(block) {
    var row = block.getFieldValue("ROW");
    var string = Blockly.Python.valueToCode(block, 'STRING', Blockly.Python.ORDER_ATOMIC);
    var color = block.getFieldValue("COLOR");
    return "oled.show_str_line(" + "str(" + string + ")," + row + "," + color + `)\n`;
};
Blockly.Python['motion_dsx_oled_fillline'] = function(block) {
    var row = block.getFieldValue("ROW");
    var color = block.getFieldValue("COLOR");
    return "oled.fill_line(" + row + "," + color + `)\n`;
};
Blockly.Python['motion_dsx_oled_clear'] = function(block) {
    var value = block.getFieldValue("VALUE");
    if(value == "0" || value == "2"){
        return `oled.fill_screen(0)\n`;
    }else{
        return `oled.fill_screen(0xff)\n`;
    }
};
Blockly.Python['motion_dsx_oled_pixel'] = function(block) {
    var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
    var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
    var state = block.getFieldValue('STATE');
    return "oled.pixel("+x+","+y+","+state+`)\n`;
};
Blockly.Python['motion_dsx_oled_progress'] = function(block) {
    var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
    var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
    var w = Blockly.Python.valueToCode(block, 'W', Blockly.Python.ORDER_ATOMIC);
    var h = Blockly.Python.valueToCode(block, 'H', Blockly.Python.ORDER_ATOMIC);
    var progress = Blockly.Python.valueToCode(block, 'PROGRESS', Blockly.Python.ORDER_ATOMIC);
    return "myUI.ProgressBar(" + x + ", " + y + ", " + w + ", " + h + ", " + progress +`)\n`;
};
Blockly.Python['motion_dsx_oled_histogram'] = function(block) {
    var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
    var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
    var w = Blockly.Python.valueToCode(block, 'W', Blockly.Python.ORDER_ATOMIC);
    var h = Blockly.Python.valueToCode(block, 'H', Blockly.Python.ORDER_ATOMIC);
    var progress = Blockly.Python.valueToCode(block, 'PROGRESS', Blockly.Python.ORDER_ATOMIC);
    var direction = block.getFieldValue('DIRECTION');
    return "myUI.stripBar(" + x + ", " + y + ", " + w + ", " + h + ", " + progress + ", " + direction +`,1)\n`;
};
Blockly.Python['motion_dsx_oled_line'] = function(block) {
    var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
    var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
    var length = Blockly.Python.valueToCode(block, 'LENGTH', Blockly.Python.ORDER_ATOMIC);
    var mode = block.getFieldValue('MODE');
    var direction = block.getFieldValue('DIRECTION');
    if(direction == "0"){
        return "oled.vline(" + x + ", " + y + ", " + length + ", " + mode +`)\n`;
    }else{
        return "oled.hline(" + x + ", " + y + ", " + length + ", " + mode +`)\n`;
    }
};
Blockly.Python['motion_dsx_oled_line2'] = function(block) {
    var x1 = Blockly.Python.valueToCode(block, 'X1', Blockly.Python.ORDER_ATOMIC);
    var y1 = Blockly.Python.valueToCode(block, 'Y1', Blockly.Python.ORDER_ATOMIC);
    var x2 = Blockly.Python.valueToCode(block, 'X2', Blockly.Python.ORDER_ATOMIC);
    var y2 = Blockly.Python.valueToCode(block, 'Y2', Blockly.Python.ORDER_ATOMIC);
    var mode = block.getFieldValue('MODE');
    return "oled.line(" + x1 + ", " + y1 + ", " + x2  + ", " + y2 + ", " + mode +`)\n`;
};
Blockly.Python['motion_dsx_oled_rect'] = function(block) {
    var mode1 = block.getFieldValue('MODE1');
    var mode2 = block.getFieldValue('MODE2');
    var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
    var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
    var w = Blockly.Python.valueToCode(block, 'W', Blockly.Python.ORDER_ATOMIC);
    var h = Blockly.Python.valueToCode(block, 'H', Blockly.Python.ORDER_ATOMIC);
    if(mode2 == "0"){
        return "oled.draw_rectangle(" + x + ", " + y + ", " + w  + ", " + h + ", " + mode1 +`)\n`;
    }else{
        return "oled.fill_rectangle(" + x + ", " + y + ", " + w  + ", " + h + ", " + mode1 +`)\n`;
    }
};
Blockly.Python['motion_dsx_oled_boarder'] = function(block) {
    var mode1 = block.getFieldValue('MODE');
    var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
    var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
    var w = Blockly.Python.valueToCode(block, 'W', Blockly.Python.ORDER_ATOMIC);
    var h = Blockly.Python.valueToCode(block, 'H', Blockly.Python.ORDER_ATOMIC);
    var r = Blockly.Python.valueToCode(block, 'R', Blockly.Python.ORDER_ATOMIC);
    return "oled.draw_round_rectangle(" + x + ", " + y + ", " + w  + ", " + h + ", " + r + ", " + mode1 +`)\n`;
};
Blockly.Python['motion_dsx_oled_circle'] = function(block) {
    var mode1 = block.getFieldValue('MODE1');
    var mode2 = block.getFieldValue('MODE2');
    var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
    var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
    var r = Blockly.Python.valueToCode(block, 'R', Blockly.Python.ORDER_ATOMIC);
    if(mode2 == "0"){
        return "oled.draw_circle(" + x + ", " + y + ", " + r + ", " + mode1 +`)\n`;
    }else{
        return "oled.fill_circle(" + x + ", " + y + ", " + r + ", " + mode1 +`)\n`;
    }
};
Blockly.Python['motion_dsx_oled_ellipse'] = function(block) {
    var mode1 = block.getFieldValue('MODE1');
    var mode2 = block.getFieldValue('MODE2');
    var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
    var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
    var rx = Blockly.Python.valueToCode(block, 'RX', Blockly.Python.ORDER_ATOMIC);
    var ry = Blockly.Python.valueToCode(block, 'RY', Blockly.Python.ORDER_ATOMIC);
    if(mode2 == "0"){
        return "oled.draw_ellipse(" + x + ", " + y + ", " + rx + ", " + ry + "," + mode1 +`)\n`;
    }else{
        return "oled.fill_ellipse(" + x + ", " + y + ", " + rx + ", " + ry + "," + mode1 +`)\n`;
    }
};
Blockly.Python['motion_dsx_oled_arc'] = function(block) {
    var mode1 = block.getFieldValue('MODE1');
    var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
    var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
    var r = Blockly.Python.valueToCode(block, 'R', Blockly.Python.ORDER_ATOMIC);
    var angle1 = Blockly.Python.valueToCode(block, 'ANGLE1', Blockly.Python.ORDER_ATOMIC);
    var angle2 = Blockly.Python.valueToCode(block, 'ANGLE2', Blockly.Python.ORDER_ATOMIC);

    return "oled.draw_arc(" + x + ", " + y + ", " + r + ", " + angle1 + ", " + angle2 + "," + mode1 +`)\n`;

};
Blockly.Python['motion_dsx_oled_triangle'] = function(block) {
    var mode1 = block.getFieldValue('MODE1');
    var mode2 = block.getFieldValue('MODE2');
    var x1 = Blockly.Python.valueToCode(block, 'X1', Blockly.Python.ORDER_ATOMIC);
    var y1 = Blockly.Python.valueToCode(block, 'Y1', Blockly.Python.ORDER_ATOMIC);
    var x2 = Blockly.Python.valueToCode(block, 'X2', Blockly.Python.ORDER_ATOMIC);
    var y2 = Blockly.Python.valueToCode(block, 'Y2', Blockly.Python.ORDER_ATOMIC);
    var x3 = Blockly.Python.valueToCode(block, 'X3', Blockly.Python.ORDER_ATOMIC);
    var y3 = Blockly.Python.valueToCode(block, 'Y3', Blockly.Python.ORDER_ATOMIC);
    if(mode2 == "0"){
        return "oled.draw_triangle(" + x1 + ", " + y1 + ", " + x2 + ", " + y2 + ", " + x3 + ", " + y3 + ", " + mode1 +`)\n`;
    }else{
        return "oled.fill_triangle(" + x1 + ", " + y1 + ", " + x2 + ", " + y2 + ", " + x3 + ", " + y3 + ", " + mode1 +`)\n`;
    }
};
Blockly.Python['motion_dsx_oled_pointer'] = function(block) {
    var mode1 = block.getFieldValue('MODE1');
    var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
    var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
    var r = Blockly.Python.valueToCode(block, 'R', Blockly.Python.ORDER_ATOMIC);
    var angle = Blockly.Python.valueToCode(block, 'ANGLE', Blockly.Python.ORDER_ATOMIC);
    return "oled.line_of_arc(" + x + ", " + y + ", " + r + ", " + angle+ ", " + mode1 + `)\n`;
};
Blockly.Python['motion_dsx_oled_scale'] = function(block) {
    var mode1 = block.getFieldValue('MODE1');
    var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
    var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
    var r = Blockly.Python.valueToCode(block, 'R', Blockly.Python.ORDER_ATOMIC);
    var angle = Blockly.Python.valueToCode(block, 'ANGLE', Blockly.Python.ORDER_ATOMIC);
    var scale = Blockly.Python.valueToCode(block, 'SCALE', Blockly.Python.ORDER_ATOMIC);
    return "oled.line_of_kedu(" + x + ", " + y + ", " + r + ", " + scale+ ", " + angle+ ", " + mode1 + `)\n`;
};

Blockly.Python['motion_dsx_oled_image2'] = function(block) {
    var image = block.getFieldValue("IMAGE");
    return "oled.bit_map(0,0,128,64,0,bytearray([" + image +`]))\n`;
};
Blockly.Python['motion_dsx_oled_image'] = function(block) {
    var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
    var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
    var image = block.getFieldValue("IMAGE");
    var imagename = block.getField("IMAGE").text_;
    var imagenameArr = imagename.split("_");
    var arrlen = imagenameArr.length;

    if(arrlen > 2){
        var w = imagenameArr[arrlen - 2];
        var h = imagenameArr[arrlen - 1];
        return "oled.bit_map(" + x + "," + y + "," + w + "," + h + ",0,bytearray([" + image +`]))\n`;
    }else{
        return "oled.bit_map(" + x + "," + y + ",128,64,0,bytearray([" + image +`]))\n`;
    }
};
Blockly.Python['motion_dsx_connect_wifi'] = function(block) {
    var ssid = Blockly.Python.valueToCode(block, 'SSID', Blockly.Python.ORDER_ATOMIC);
    var password = Blockly.Python.valueToCode(block, 'PASSWORD', Blockly.Python.ORDER_ATOMIC);
    return "network.connectWifi(" + ssid + "," + password + `)\n`;
};
Blockly.Python['motion_dsx_isconnected'] = function(block) {
    return ["network.isconnected()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_getip'] = function(block) {
    return ["network.ifconfig()[0]", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_init_i2c'] = function(block) {
    var freq = Blockly.Python.valueToCode(block, 'FREQ', Blockly.Python.ORDER_ATOMIC);
    return "iic = I2C(0,freq=" + freq + `)\n`;
};
Blockly.Python['motion_dsx_close_i2c'] = function(block) {
    var index = block.getFieldValue("INDEX");
    return "i2c"+index+`.deinit()\n`;
};
Blockly.Python['motion_dsx_i2c_write'] = function(block) {
    var addr = Blockly.Python.valueToCode(block, 'ADDR', Blockly.Python.ORDER_ATOMIC);
    var value = Blockly.Python.valueToCode(block, 'VALUE', Blockly.Python.ORDER_ATOMIC);
    
    if(value.startsWith(`'`)&&value.endsWith(`'`)){
        value = value.slice(1,-1);
    }
    return "iic.write("+ addr + ",bytes([" + value + `]))\n`;
};
Blockly.Python['motion_dsx_i2c_read'] = function(block) {
    var addr = Blockly.Python.valueToCode(block, 'ADDR', Blockly.Python.ORDER_ATOMIC);
    var len = Blockly.Python.valueToCode(block, 'LEN', Blockly.Python.ORDER_ATOMIC);
    return ["iic.read("+ addr + "," + len +")",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_i2c_scan'] = function(block) {
    return ["iic.scan()",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_disconnect_wifi'] = function(block) {
    return `network.disconnectWifi()\n`;
};
Blockly.Python['motion_dsx_start_hotspot'] = function(block) {
    var ssid = Blockly.Python.valueToCode(block, 'SSID', Blockly.Python.ORDER_ATOMIC);
    var password = Blockly.Python.valueToCode(block, 'PASSWORD', Blockly.Python.ORDER_ATOMIC);
    return "network.startHotspot(" + ssid + "," + password + `)\n`;
};
Blockly.Python['motion_dsx_config_hotspot'] = function(block) {
    var ip = Blockly.Python.valueToCode(block, 'IP', Blockly.Python.ORDER_ATOMIC);
    var netmask = Blockly.Python.valueToCode(block, 'NETMASK', Blockly.Python.ORDER_ATOMIC);
    var gw = Blockly.Python.valueToCode(block, 'GATEWAY', Blockly.Python.ORDER_ATOMIC);
    return "network.configHotspot(" + ip + "," + netmask + "," + gw + `)\n`;
};
Blockly.Python['motion_dsx_stop_hotspot'] = function(block) {
    return `network.stopHotspot()\n`;
};
Blockly.Python['motion_dsx_socket_create'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
    if(name.startsWith(`'`)&&name.endsWith(`'`)){
        name = name.slice(1,-1);
    }
    var type = block.getFieldValue("TYPE");
    var type2 = block.getFieldValue("TYPE2");
    return name + " = socket.socket(socket."+type+", socket."+type2+`)\n`;
};
Blockly.Python['motion_dsx_socket_close'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
    if(name.startsWith(`'`)&&name.endsWith(`'`)){
        name = name.slice(1,-1);
    }
    return name + `.close()\n`;
};
Blockly.Python['motion_dsx_socket_bind'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
    if(name.startsWith(`'`)&&name.endsWith(`'`)){
        name = name.slice(1,-1);
    }
    var addr = Blockly.Python.valueToCode(block, 'ADDR', Blockly.Python.ORDER_ATOMIC);
    var port = Blockly.Python.valueToCode(block, 'PORT', Blockly.Python.ORDER_ATOMIC);
    return name + ".bind(("+addr+", "+port+`))\n`;
};
Blockly.Python['motion_dsx_socket_timeout'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
    if(name.startsWith(`'`)&&name.endsWith(`'`)){
        name = name.slice(1,-1);
    }
    var timeout = Blockly.Python.valueToCode(block, 'TIMEOUT', Blockly.Python.ORDER_ATOMIC);
    return name + ".settimeout("+timeout+`)\n`;
};
Blockly.Python['motion_dsx_socket_listen'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
    if(name.startsWith(`'`)&&name.endsWith(`'`)){
        name = name.slice(1,-1);
    }
    var count = Blockly.Python.valueToCode(block, 'COUNT', Blockly.Python.ORDER_ATOMIC);
    return name + ".listen("+count+`)\n`;
};
Blockly.Python['motion_dsx_socket_setbroadcast'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
    if(name.startsWith(`'`)&&name.endsWith(`'`)){
        name = name.slice(1,-1);
    }
    var count = Blockly.Python.valueToCode(block, 'COUNT', Blockly.Python.ORDER_ATOMIC);
    return name + `.setsockopt(socket.SOL_SOCKET,socket.SO_BROADCAST,1)\n`;
};
Blockly.Python['motion_dsx_socket_connect'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
    if(name.startsWith(`'`)&&name.endsWith(`'`)){
        name = name.slice(1,-1);
    }
    var addr = Blockly.Python.valueToCode(block, 'HOST', Blockly.Python.ORDER_ATOMIC);
    var port = Blockly.Python.valueToCode(block, 'PORT', Blockly.Python.ORDER_ATOMIC);
    return ["("+name + ".connect(("+addr+", "+port+")) == 0)", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_socket_accept'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
    if(name.startsWith(`'`)&&name.endsWith(`'`)){
        name = name.slice(1,-1);
    }
    return [name + ".accept()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_socket_send'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
    if(name.startsWith(`'`)&&name.endsWith(`'`)){
        name = name.slice(1,-1);
    }
    var content = Blockly.Python.valueToCode(block, 'CONTENT', Blockly.Python.ORDER_ATOMIC);
    return name + ".send("+content+`)\n`;
};
Blockly.Python['motion_dsx_socket_sendto'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
    if(name.startsWith(`'`)&&name.endsWith(`'`)){
        name = name.slice(1,-1);
    }
    var content = Blockly.Python.valueToCode(block, 'CONTENT', Blockly.Python.ORDER_ATOMIC);
    var addr = Blockly.Python.valueToCode(block, 'ADDR', Blockly.Python.ORDER_ATOMIC);
    if(addr.startsWith(`'`)&&addr.endsWith(`'`)){
        addr = addr.slice(1,-1);
    }
    var port = Blockly.Python.valueToCode(block, 'PORT', Blockly.Python.ORDER_ATOMIC);
    if(port.startsWith(`'`)&&port.endsWith(`'`)){
        port = port.slice(1,-1);
    }
    return name + ".sendto("+content+`,(\"`+addr + `\",` + port +`))\n`;
};
Blockly.Python['motion_dsx_socket_recv'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
    if(name.startsWith(`'`)&&name.endsWith(`'`)){
        name = name.slice(1,-1);
    }
    return [name + ".recv()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_socket_recvfrom'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
    if(name.startsWith(`'`)&&name.endsWith(`'`)){
        name = name.slice(1,-1);
    }
    var len = Blockly.Python.valueToCode(block, 'LENGTH', Blockly.Python.ORDER_ATOMIC);
    return [name + ".recvfrom("+len+")", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_conn_create_server'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var port = Blockly.Python.valueToCode(block, 'PORT', Blockly.Python.ORDER_ATOMIC);
    var count = Blockly.Python.valueToCode(block, 'COUNT', Blockly.Python.ORDER_ATOMIC);
    return `dsx_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM);dsx_server.bind(('0.0.0.0',` + port + "));dsx_server.listen(" + count + `);_thread.start_new_thread(dsx_server_thread,())\n`;
};
Blockly.Python['motion_dsx_conn_create_client'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    return `dsx_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)\n`;
};
Blockly.Python['motion_dsx_conn_connect'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var addr = Blockly.Python.valueToCode(block, 'HOST', Blockly.Python.ORDER_ATOMIC);
    var port = Blockly.Python.valueToCode(block, 'PORT', Blockly.Python.ORDER_ATOMIC);
    return ["(dsx_client.connect(("+addr+", "+port+")) == 0)", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_conn_accept'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var name = block.getFieldValue("SOCKET");
    return name + ` = dsx_server.accept()\n`;
};
Blockly.Python['motion_dsx_conn_hasconn'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    return ["dsx_conn_cnt() > 0", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_conn_getconn'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    return ["get_dsxclient()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_conn_send'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var name = Blockly.Python.valueToCode(block, 'SOCKET', Blockly.Python.ORDER_ATOMIC);
    var content = Blockly.Python.valueToCode(block, 'CONTENT', Blockly.Python.ORDER_ATOMIC);
    return name + ".send("+content+`)\n`;
};
Blockly.Python['motion_dsx_conn_recv'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var name = Blockly.Python.valueToCode(block, 'SOCKET', Blockly.Python.ORDER_ATOMIC);
    return [name + ".recv()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_conn_client_send'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var content = Blockly.Python.valueToCode(block, 'CONTENT', Blockly.Python.ORDER_ATOMIC);
    return "dsx_client.send("+content+`)\n`;
};
Blockly.Python['motion_dsx_conn_client_recv'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var name = block.getFieldValue("SOCKET");
    return ["dsx_client.recv()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_conn_close_server'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    return `dsx_server.close()\n`;
};
Blockly.Python['motion_dsx_conn_close_client'] = function(block) {
    Blockly.Python.definitions_['import_socket'] = `import socket\n`;
    var name = block.getFieldValue("SOCKET");
    return `dsx_client.close()\n`;
};
Blockly.Python['motion_dsx_digital_pin'] = function(block) {
    var pin = block.getFieldValue("PIN");
    var state = block.getFieldValue("STATE");
    return ["(pin" + pin + ".value() == " + state + ")", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_analog_pin'] = function(block) {
    var pin = block.getFieldValue("PIN");
    return ["adc" + pin + ".read()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_set_digital_pin'] = function(block) {
    var pin = block.getFieldValue("PIN");
    var state = block.getFieldValue("STATE");
    return "pin" + pin + " = Pin(" + pin + ",mode=Pin.OUT,pull=Pin.PULL_UP);" + "pin" + pin + ".value("+state+`)\n`;
};
Blockly.Python['motion_dsx_set_analog_pin_freq'] = function(block) {
    var pin = block.getFieldValue("PIN");
    var freq = Blockly.Python.valueToCode(block, 'FREQ', Blockly.Python.ORDER_ATOMIC);
    return "pwm" + pin + ".freq(" + freq + `)\n`;
};
Blockly.Python['motion_dsx_set_analog_pin_duty'] = function(block) {
    var pin = block.getFieldValue("PIN");
    var freq = Blockly.Python.valueToCode(block, 'DUTY', Blockly.Python.ORDER_ATOMIC);
    return "pwm" + pin + ".duty(" + freq + `)\n`;
};

Blockly.Python['motion_dsx_unisound'] = function(block) {
    return ["us516p6.recognition()", Blockly.Python.ORDER_ATOMIC];
};

Blockly.Python['motion_dsx_unisound_value'] = function(block) {
    var index = block.getFieldValue("INDEX");
    return [index, Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_uart_canread'] = function(block) {
    var index = block.getFieldValue("INDEX");
    return ["uart.any()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_init_uart'] = function(block) {
    var index = block.getFieldValue("INDEX");
    var baud = block.getFieldValue("BAUD");
    return "uart = UART(2, baudrate="+baud+`, timeout=0xffff)\n`;
};
Blockly.Python['motion_dsx_uart_isinit'] = function(block) {
    var index = block.getFieldValue("INDEX");
    return ["(uart != 0)",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_close_uart'] = function(block) {
    var index = block.getFieldValue("INDEX");
    return `uart.deinit()\n`;
};
Blockly.Python['motion_dsx_uart_write'] = function(block) {
    var index = block.getFieldValue("INDEX");
    var value = Blockly.Python.valueToCode(block, 'VALUE', Blockly.Python.ORDER_ATOMIC);
    var ends = block.getFieldValue("ENDS");
    if(ends == "n"){
        return "uart.write("+value+`+chr(13))\n`;
    }else{
        return "uart.write("+value+`)\n`;
    }
};
Blockly.Python['motion_dsx_uart_write2'] = function(block) {
    var index = block.getFieldValue("INDEX");
    var value = Blockly.Python.valueToCode(block, 'VALUE', Blockly.Python.ORDER_ATOMIC);
    if(value.startsWith(`'`)&&value.endsWith(`'`)){
        value = value.slice(1,-1);
    }
    return "uart.write(bytes(["+value+`]))\n`;
};
Blockly.Python['motion_dsx_uart_read'] = function(block) {
    var index = block.getFieldValue("INDEX");
    var value = Blockly.Python.valueToCode(block, 'VALUE', Blockly.Python.ORDER_ATOMIC);
    return ["uart.read(" + value + ")",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dsx_uart_readline'] = function(block) {
    var index = block.getFieldValue("INDEX");
    return ["uart.readline()",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_hw_set_motor'] = function(block) {
    var motor = block.getFieldValue("MOTOR_INDEX");
    var direction = block.getFieldValue("DIRECTION");
    var speed = Blockly.Python.valueToCode(block, 'SPEED', Blockly.Python.ORDER_ATOMIC);
    return "hw_board.motor_speed(" + motor+","+direction+","+ speed + `)\n`;
};
Blockly.Python['motion_hw_get_motor'] = function(block) {
    var motor = block.getFieldValue("MOTOR_INDEX");
    return "hw_board.motor_speed(" + motor + `)\n`;
};
Blockly.Python['motion_hw_stop_motor'] = function(block) {
    var motor = block.getFieldValue("MOTOR_INDEX");
    return "hw_board.motor_stop(" + motor + `)\n`;
};
Blockly.Python['motion_hw_set_light'] = function(block) {
    var state = block.getFieldValue("STATE");
    return "pin8 = Pin(8,mode=Pin.OUT,pull=Pin.PULL_UP);" + "pin8.value("+state+`)\n`;
};
Blockly.Python['motion_hw_set_servo'] = function(block) {
    var pin = block.getFieldValue("PIN");
    var angle = Blockly.Python.valueToCode(block, 'ANGLE', Blockly.Python.ORDER_ATOMIC);
    return "hw_board.servo_angle("+pin+","+angle+`)\n`;
};
Blockly.Python['motion_pz_set_servo'] = function(block) {
    var pin = block.getFieldValue("PIN");
    var angle = Blockly.Python.valueToCode(block, 'ANGLE', Blockly.Python.ORDER_ATOMIC);
    return "servoAngle("+pin+","+angle+`)\n`;
};
Blockly.Python['motion_pz_set_motor'] = function(block) {
    var motor = block.getFieldValue("MOTOR_INDEX");
    var direction = block.getFieldValue("DIRECTION");
    var speed = Blockly.Python.valueToCode(block, 'SPEED', Blockly.Python.ORDER_ATOMIC);
    return "motorRun(" + motor+","+direction+","+ speed + `)\n`;
};
Blockly.Python['motion_pz_stop_motor'] = function(block) {
    var motor = block.getFieldValue("MOTOR_INDEX");
    return "motorStop(" + motor + `)\n`;
};
Blockly.Python['motion_pz_set_light'] = function(block) {
    var state = block.getFieldValue("STATE");
    return "pin8 = Pin(8,mode=Pin.OUT,pull=Pin.PULL_UP);" + "pin8.value("+state+`)\n`;
};
Blockly.Python['motion_set_servo'] = function(block) {
    var pin = block.getFieldValue("PIN");
    var angle = Blockly.Python.valueToCode(block, 'ANGLE', Blockly.Python.ORDER_ATOMIC);
    return "servo"+pin+".angle("+angle+`)\n`;
};
Blockly.Python['motion_set_motor'] = function(block) {
    var motor = block.getFieldValue("MOTOR_INDEX");
    var direction = block.getFieldValue("DIRECTION");
    var speed = Blockly.Python.valueToCode(block, 'SPEED', Blockly.Python.ORDER_ATOMIC);
    return "motor.speed(" + motor+","+direction+","+ speed + `)\n`;
    
};
Blockly.Python['motion_stop_motor'] = function(block) {
    var motor = block.getFieldValue("MOTOR_INDEX");
    return "motor.stop(" + motor + `)\n`;
};
Blockly.Python['motion_carrobot_get_sonic'] = function(block) {
    return ["ultra_14_13.distance()",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_carrobot_get_tracked_init'] = function(block) {
    var state = block.getFieldValue("STATE");
    window.motion_carrobot_get_tracked_init = parseInt(state);
    return "";
};
Blockly.Python['motion_carrobot_get_tracked'] = function(block) {
    var pin = block.getFieldValue("PIN");
    if(window.motion_carrobot_get_tracked_init!=undefined){
        return ["(pin" + pin + ".value() == "+window.motion_carrobot_get_tracked_init+")",Blockly.Python.ORDER_ATOMIC];
    }
    return ["(pin" + pin + ".value() == 1)",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_carrobot_set_motor'] = function(block) {
    var motor = block.getFieldValue("MOTOR_INDEX");
    var direction = block.getFieldValue("DIRECTION");
    var speed = Blockly.Python.valueToCode(block, 'SPEED', Blockly.Python.ORDER_ATOMIC);
    return "motorRun(" + motor+","+direction+","+ speed + `)\n`;
};
Blockly.Python['motion_carrobot_stop_motor'] = function(block) {
    var motor = block.getFieldValue("MOTOR_INDEX");
    return "motorStop(" + motor + `)\n`;
};

Blockly.Python['motion_carrobot_set_light'] = function(block) {
    var state = block.getFieldValue("STATE");
    var index = block.getFieldValue("INDEX");
    return "pin"+index+" = Pin("+index+",mode=Pin.OUT,pull=Pin.PULL_UP);" + "pin"+index+".value("+state+`)\n`;
};
Blockly.Python['motion_edu_get_sonic'] = function(block) {
    return ["ultra_2_15.distance()",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_edu_get_pm25'] = function(block) {
    return ["pm.get_pm2_5()",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_edu_get_soil'] = function(block) {
    return ["adc13.read()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_edu_get_light'] = function(block) {
    var pin = block.getFieldValue("PIN");
    return ["adc13.read()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_edu_get_blocked2'] = function(block) {
    var pin = block.getFieldValue("PIN");
    return ["(adc1.read())",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_edu_get_key'] = function(block) {
    var state = block.getFieldValue("STATE");
    return ["(pin13.value() == " + state + ")", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_edu_fan'] = function(block) {
    var state = block.getFieldValue("STATE");
    if(state == 0){
        return `pin2 = Pin(2,mode=Pin.OUT,pull=Pin.PULL_UP);pin2.value(0);pin5 = Pin(5,mode=Pin.OUT,pull=Pin.PULL_UP);pin5.value(1);\n`;
    }else{
        return `pin2 = Pin(2,mode=Pin.OUT,pull=Pin.PULL_UP);pin2.value(1);pin5 = Pin(5,mode=Pin.OUT,pull=Pin.PULL_UP);pin5.value(0);\n`;
    }
};
Blockly.Python['motion_edu_pump'] = function(block) {
    var state = block.getFieldValue("STATE");
    if(state == 0){
        return `pin2 = Pin(2,mode=Pin.OUT,pull=Pin.PULL_UP);pin2.value(0);pin5 = Pin(5,mode=Pin.OUT,pull=Pin.PULL_UP);pin5.value(1);\n`;
    }else{
        return `pin2 = Pin(2,mode=Pin.OUT,pull=Pin.PULL_UP);pin2.value(1);pin5 = Pin(5,mode=Pin.OUT,pull=Pin.PULL_UP);pin5.value(0);\n`;
    }
};
Blockly.Python['motion_edu_get_flame2'] = function(block) {
    return ["adc1.read()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_edu_get_smoke2'] = function(block) {
    return ["adc14.read()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_edu_dht_temperature'] = function(block) {
    return ["dht14.temp()",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_edu_dht_humidity'] = function(block) {
    return ["dht14.humi()",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_edu_set_light'] = function(block) {
    var state = block.getFieldValue("STATE");
    return "pin14 = Pin(14,mode=Pin.OUT,pull=Pin.PULL_UP);" + "pin14.value("+state+`)\n`;
};
Blockly.Python['motion_edu_set_servo'] = function(block) {
    var angle = Blockly.Python.valueToCode(block, 'ANGLE', Blockly.Python.ORDER_ATOMIC);
    return "servo8.angle("+angle+`)\n`;
};
Blockly.Python['motion_edu_matrix_key_init'] = function(block) {
    var state = block.getFieldValue("STATE");
    window.motion_edu_matrix_key_init = parseInt(state);
    return "";
};
Blockly.Python['motion_edu_matrix_key'] = function(block) {
    var index = block.getFieldValue("INDEX");
    var state = block.getFieldValue("STATE");
    var indexHead = index.substr(0,2);
    var indexTail = index.substr(2);
    if(window.motion_edu_matrix_key_init != undefined){
        indexTail = indexTail.replaceAll("0","a");
        indexTail = indexTail.replaceAll("1","b");
        if(window.motion_edu_matrix_key_init == 1){
            indexTail = indexTail.replaceAll("a","0");
            indexTail = indexTail.replaceAll("b","1");
        }else{
            indexTail = indexTail.replaceAll("a","1");
            indexTail = indexTail.replaceAll("b","0");
        }
        index = indexHead + indexTail;
    }
    if(state == 0){
        return ["((ttp_2_15.get_key() & " + index + ") == " + index+")",Blockly.Python.ORDER_ATOMIC];
    }else{
        return ["((ttp_2_15.get_key() & " + index + ") == 0)",Blockly.Python.ORDER_ATOMIC];
    }
};
Blockly.Python['motion_get_sonic'] = function(block) {
    var pin1 = block.getFieldValue("PIN1");
    var pin2 = block.getFieldValue("PIN2");
    return ["ultra_" + pin1 + "_" + pin2 + ".distance()",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dht_temperature'] = function(block) {
    var pin = block.getFieldValue("PIN");
    return ["dht"+pin+".temp()",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_dht_humidity'] = function(block) {
    var pin = block.getFieldValue("PIN");
    return ["dht"+pin+".humi()",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_matrix_key_init'] = function(block) {
    var state = block.getFieldValue("STATE");
    window.motion_matrix_key_init = parseInt(state);
    return "";
};
Blockly.Python['motion_matrix_key'] = function(block) {
    var scl = block.getFieldValue("SCL");
    var sdo = block.getFieldValue("SDO");
    var index = block.getFieldValue("INDEX");
    var state = block.getFieldValue("STATE");
    var indexHead = index.substr(0,2);
    var indexTail = index.substr(2);
    if(window.motion_matrix_key_init != undefined){
        indexTail = indexTail.replaceAll("0","a");
        indexTail = indexTail.replaceAll("1","b");
        if(window.motion_matrix_key_init == 1){
            indexTail = indexTail.replaceAll("a","0");
            indexTail = indexTail.replaceAll("b","1");
        }else{
            indexTail = indexTail.replaceAll("b","1");
            indexTail = indexTail.replaceAll("a","0");
            index = indexHead + indexTail;
            if(state == 0){
                return ["((ttp_"+scl + "_" + sdo + ".get_key() & " + index + ") == 0)",Blockly.Python.ORDER_ATOMIC];
            }else{
                return ["((ttp_"+scl + "_" + sdo + ".get_key() & " + index + "))",Blockly.Python.ORDER_ATOMIC];
            }
        }
        index = indexHead + indexTail;
    }
    if(state == 0){
        return ["((ttp_"+scl + "_" + sdo + ".get_key() & " + index + ") == " + index+")",Blockly.Python.ORDER_ATOMIC];
    }else{
        return ["((ttp_"+scl + "_" + sdo + ".get_key() & " + index + ") == 0)",Blockly.Python.ORDER_ATOMIC];
    }
};
Blockly.Python['motion_get_pm25'] = function(block) {
    return ["pm.get_pm2_5()",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_get_soil'] = function(block) {
    var pin = block.getFieldValue("PIN");
    return ["adc" + pin + ".read()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_get_flame'] = function(block) {
    var pin = block.getFieldValue("PIN");
    if(window.motion_get_flame_init!=undefined){
        return ["(pin" + pin + ".value() == "+window.motion_get_flame_init+")",Blockly.Python.ORDER_ATOMIC];
    }
    return ["(pin" + pin + ".value() == 1)",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_get_flame_init'] = function(block) {
    var state = block.getFieldValue("STATE");
    window.motion_get_flame_init = parseInt(state);
    return "";
};
Blockly.Python['motion_get_flame2'] = function(block) {
    var pin = block.getFieldValue("PIN");
    return ["adc" + pin + ".read()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_get_smoke_init'] = function(block) {
    var state = block.getFieldValue("STATE");
    window.motion_get_smoke_init = parseInt(state);
    return "";
};
Blockly.Python['motion_get_smoke'] = function(block) {
    var pin = block.getFieldValue("PIN");
    if(window.motion_get_smoke_init!=undefined){
        return ["(pin" + pin + ".value() == "+window.motion_get_smoke_init+")",Blockly.Python.ORDER_ATOMIC];
    }
    return ["(pin" + pin + ".value() == 0)",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_get_smoke2'] = function(block) {
    var pin = block.getFieldValue("PIN");
    return ["adc" + pin + ".read()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_get_infrared_init'] = function(block) {
    var state = block.getFieldValue("STATE");
    window.motion_get_infrared_init = parseInt(state);
    return "";
};
Blockly.Python['motion_get_infrared'] = function(block) {
    var pin = block.getFieldValue("PIN");
    if(window.motion_get_infrared_init!=undefined){
        return ["(pin" + pin + ".value() == "+window.motion_get_infrared_init+")",Blockly.Python.ORDER_ATOMIC];
    }
    return ["(pin" + pin + ".value() == 0)",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_get_light'] = function(block) {
    var pin = block.getFieldValue("PIN");
    return ["adc" + pin + ".read()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_get_gray'] = function(block) {
    var pin = block.getFieldValue("PIN");
    return ["adc" + pin + ".read()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_get_airpressure'] = function(block) {
    return ["barometer.read()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_get_raindrop_init'] = function(block) {
    var state = block.getFieldValue("STATE");
    window.motion_get_raindrop_init = parseInt(state);
    return "";
};
Blockly.Python['motion_get_raindrop'] = function(block) {
    var pin = block.getFieldValue("PIN");
    if(window.motion_get_raindrop_init!=undefined){
        return ["(pin" + pin + ".value() == "+window.motion_get_raindrop_init+")",Blockly.Python.ORDER_ATOMIC];
    }
    return ["(pin" + pin + ".value() == 0)",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_get_raindrop2'] = function(block) {
    var pin = block.getFieldValue("PIN");
    return ["adc" + pin + ".read()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_get_blocked_init'] = function(block) {
    var state = block.getFieldValue("STATE");
    window.motion_get_blocked_init = parseInt(state);
    return "";
};
Blockly.Python['motion_get_blocked'] = function(block) {
    var pin = block.getFieldValue("PIN");
    if(window.motion_get_blocked_init!=undefined){
        return ["(pin" + pin + ".value() == "+window.motion_get_blocked_init+")",Blockly.Python.ORDER_ATOMIC];
    }
    return ["(pin" + pin + ".value() == 1)",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_get_blocked2'] = function(block) {
    var pin = block.getFieldValue("PIN");
    return ["(adc" + pin + ".read())",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_get_heartbeat'] = function(block) {
    return ["heartbeat.read()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_get_tur_init'] = function(block) {
    var state = block.getFieldValue("STATE");
    window.motion_get_tur_init = parseInt(state);
    return "";
};
Blockly.Python['motion_get_tur'] = function(block) {
    var pin = block.getFieldValue("PIN");
    return ["adc" + pin + ".read()", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_get_tur2'] = function(block) {
    var pin = block.getFieldValue("PIN");
    if(window.motion_get_tur_init!=undefined){
        return ["(pin" + pin + ".value() == "+window.motion_get_tur_init+")",Blockly.Python.ORDER_ATOMIC];
    }
    return ["(pin" + pin + ".value() == 1)",Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['motion_set_light'] = function(block) {
    var pin = block.getFieldValue("PIN");
    var state = block.getFieldValue("STATE");
    return "pin" + pin + " = Pin(" + pin + ",mode=Pin.OUT,pull=Pin.PULL_UP);" + "pin" + pin + ".value("+state+`)\n`;
};
Blockly.Python['motion_mp3_set_vol'] = function(block) {
    var vol = Blockly.Python.valueToCode(block, 'VOL', Blockly.Python.ORDER_ATOMIC);
    return `mp3.setvol(` + vol + `)\n`;
};
Blockly.Python['motion_mp3_play'] = function(block) {
    return `mp3.play()\n`;
};
Blockly.Python['motion_mp3_pause'] = function(block) {
    return `mp3.pause()\n`;
};
Blockly.Python['motion_mp3_stop'] = function(block) {
    return `mp3.stop()\n`;
};
Blockly.Python['motion_mp3_next'] = function(block) {
    return `mp3.next()\n`;
};
Blockly.Python['motion_mp3_pre'] = function(block) {
    return `mp3.pre()\n`;
};
Blockly.Python['motion_get_key'] = function(block) {
    var index = block.getFieldValue("PIN");
    var state = block.getFieldValue("STATE");
    return ["(pin" + index + ".value() == " + state + ")", Blockly.Python.ORDER_ATOMIC];
};
Blockly.Python['event_main_thread'] = function(block) {
    return `def main():\n`;
};
Blockly.Python['event_sub_thread'] = function(block) {
    return `def thread():\n`;
};