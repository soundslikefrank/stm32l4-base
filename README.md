# stm32f3-base
A clean (and very simple) base for stm32f3xx projects based on cmake

# To start with your STM32F3xx project

1) Clone this repository:

```
git clone --recursive https://github.com/soundslikefrank/stm32f3-base.git my-cool-project
```

2) Now we need to make a few adjustments. Use STM32CubeMX to generate code for your MCU/board (leave all default values), but use `Makefile` as Toolchain / IDE
2) Copy these files to the corresponding locations (adjust file names):

  `STM32CubeMXProject/startup_stm32f3xxxx.s` -> `./startup_stm32f3xxxx.s`
  `STM32CubeMXProject/STM32F3xxxxxx_FLASH.ld` -> `./STM32F3xxxxxx_FLASH.ld`

Then you can remove the old corresponding old files that come with this project.

3) Adjust the references to these files in the `CMakeLists.txt`:

```cmake
# Set startup file in project files:
set(PROJECT_FILES
  # ...

  startup_stm32f3xxxx.s
  )
```

and


```cmake
# If you're not sure which identifier to use, look into the STM32CubeMX generated Makefile
target_compile_definitions(${EXECUTABLE} PRIVATE
  -DUSE_HAL_DRIVER
  -DSTM32F3xxxx # change this!
  )
```

and

```cmake
target_link_options(${EXECUTABLE} PRIVATE
  -T${CMAKE_SOURCE_DIR}/STM32F3xxxxxx_FLASH.ld
```

4) -_optional_- You might want to do some clock configuration (using STM32CubeMX or editing the file `system_stm32f3xx.c` directly), especially if you're using an external crystal

5) -_optional_- Uncomment HAL modules that you don't need in `include/stm32f3xx_hal_conf.h` and `CMakeLists.txt`

6) To build (we are assuming an [out-of-source build](https://gitlab.kitware.com/cmake/community/-/wikis/FAQ#out-of-source-build-trees)):

```bash
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../arm-none-eabi-gcc.cmake ..
make # or directly
make upload # use OpenOCD to flash!
```

You only ever need to run the `cmake` command again after you made changes to the CMakeLists.txt.
