# libocr cpp
用于 ocr 的简单 c++ 库

[![CMake](https://github.com/GengGode/libocr/actions/workflows/cmake.yml/badge.svg)](https://github.com/GengGode/libocr/actions/workflows/cmake.yml)

中文 | [English](https://github.com/GengGode/libocr/blob/main/README.md)

## 简介：我为什么写这个库

> 我经常有一些小的想法，它们需要一个OCR的功能。
> 
> 但我不想使用 python 或 java 库，因为它不便于集成。
> 而且也不能使用一些 WebApi ，一方面它们无法在脱机下使用，另一方面它们普遍是收费的。
> 并且我不想用一些很大的库比如 PaddleOCR、Tesseract，因为用起来太不方便了，普遍性的要加载模型等。
> 
> 所以我写了这个库！
> 
> 使用非常简单，只需要加载图片并调用函数，就可以得到结果，它内嵌了一个较好的模型。
> 
> 用于一些可以获取到处理过的图片的项目，比如我写的一个小工具，用于识别原神游戏界面中的文字，然后自动点击及记录。

> 缺点是需要传入处理过的图片，因为没有加入前处理模块如文字检测、语种识别、方向识别等。（在某些场景下我们很容易获取到文字的感兴趣区域，只需要一些简单的传统算法）
>
> 优点是非常易用，可以很容易的集成到项目中。

## 用法：易于使用

> 将 **libocr.dll** 和 **libocr.lib** 复制到您的项目的 lib 文件夹

> 将 **libocr.h** 复制到您的项目 include 文件夹

然后你可以像这样使用它：

```cpp
#include "libocr.h"
#include <iostream>
int main() {
    std::string image_path = "test.jpg";
    std::string text;
    //=========================================================================
    {
        char *result = libocr::ocr_rec(image_path.c_str(), image_path.size());
        text = std::string(result);
        libocr::free_char(result);
    }
    //=========================================================================
    std::cout << text << std::endl;
    return 0;
}
```

## 编译：从源码编译

- 您需要安装 **CMake** / **Clion** / **Visual Studio 2022**
- 克隆这个项目
 ```shell
git clone https://github.com/GengGode/libocr.git
cd libocr
```
- 解压部分压缩依赖库 3rdparty/resource/*.zip to 3rdparty/staticlib/
```shell
cd 3rdparty/resource
unzip *.zip
```
- 编译
```shell
cd ../..
mkdir build
cd build
cmake ..
MSBuild libocr.sln /p:Configuration=Release
```

## 自定义：自定义您的模型

- 可以使用自己的模型替换库中的模型
- 你需要把你的模型放在 **resource/\*.onnx** 和 **resource/\*.txt** 文件夹中
- 重新编译库
