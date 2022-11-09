# libocr cpp
a simple c++ library for ocr

[中文]() | English

## Profile : Why I write this library

> I often have some small ideas. They need an OCR function.
> 
> But I don't want to use python or java libraries because they are not easy to integrate.
> Moreover, some WebApi cannot be used. On the one hand, they cannot be used offline, and on the other hand, they are generally charged.
> And I don't want to use some large libraries, such as PaddleOCR and Tesseract, because it is too inconvenient to use. Generally, models need to be loaded.
> 
> So I wrote this library!
> 
> It is very simple to use. You only need to load images and call functions to get results. It has a better model embedded.
> 
> It is used for some projects that can obtain processed pictures, such as a gadget I wrote, which is used to identify the text in the Genshin Impact game interface, and then automatically click and record.
> The disadvantage is that the processed images need to be imported, because there is no pre-processing module added, such as text detection, language recognition, direction recognition, etc. (In some scenarios, we can easily obtain the region of interest of the text, and we only need some simple traditional algorithms.)
> 
> The advantage is that it is very easy to use and can be easily integrated into the project.

## Usage : Easy to use


> Copy **libocr.dll** and **libocr.lib** to your project lib folder

> Copy **libocr.h** to your project include folder

And then you can use it like this:
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

## Build : Build from source

- You need to install **CMake** / **Clion** / **Visual Studio 2022** 
- Clone this project
 ```shell
git clone https://github.com/GengGode/libocr.git
cd libocr
```
- Unzip 3rdparty/resource/*.zip to 3rdparty/staticlib/
```shell
cd 3rdparty/resource
unzip *.zip
```
- Build
```shell
cd ../..
mkdir build
cd build
cmake ..
MSBuild libocr.sln /p:Configuration=Release
```

## Customize : Customize your model

- You can use your own model to replace the model in the library
- You need to put your model in the **resource/\*.onnx** and **resource/\*.txt** folder
- Rebuild the library