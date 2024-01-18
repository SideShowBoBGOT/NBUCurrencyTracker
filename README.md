<a name="readme-top"></a>
# NBUCurrencyTracker

NBUCurrencyTracker is an application in C++ to fetch currency 
rates using data from the National Bank of Ukraine (NBU) API.

![Screenshot](Docs/Screenshot%20from%202024-01-18%2009-20-29.png)

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [Libraries](#libraries)
- [Code structure](#code-structure)
- [Contact](#contact)
- [License](#license)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Installation
1. Clone the repository and update submodules:
```sh
git clone https://github.com/SideShowBoBGOT/NBUCurrencyTracker
git submodule update --init --recursive
```
2. Enter the repository directory and build the project with CMake 3.27 or higher:
```sh
cd NBUCurrencyTracker
cmake -S . -B build
cmake --build build -j 12
```

3. Create a config file. Set up the config file "config.toml":
```toml
# Working directory is set to the one where the config is located
logFileName = "logs.txt"
outputFileName = "out.txt"
fileType = "JSON"
#fileType = "XML"
intervalMillis = 2000
```
4. Launch the application by providing the path to the config file as parameter:
```sh
./build/Main -c config.toml
```
<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Usage

### User Interface

An user can dynamically change the type of the data format of the output file: JSON or XML. And also the user can change the interval between updates in seconds:

![Screenshot](Docs/Screenshot%20from%202024-01-18%2010-57-39.png)
![Screenshot](Docs/Screenshot%20from%202024-01-18%2010-45-11.png)

### Error messages

If any issues encountered while trying to fetch the data from the API or save it to the file, a corresponding message appears:

![Screenshot](Docs/Screenshot%20from%202024-01-18%2010-49-14.png)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Libraries
The project uses a number of external libraries:
* [CLI11](https://github.com/CLIUtils/CLI11) is used to simplify creation of command line interfaces.
* [cpp-httplib](https://github.com/yhirose/cpp-httplib) is used to make calls to the NBU API.
* [fmt](https://github.com/fmtlib/fmt) is used to simplify formatting strings. Also it provides more functionalities than C++20 formatting library.
* [FTXUI](https://github.com/SideShowBoBGOT/FTXUI) is text user interface library. Due to the fact that many classes are declared inside .cpp-files, it has been forked and some changes have been made.
* [json](https://github.com/nlohmann/json) is used to parse json data.
* [magic_enum](https://github.com/Neargye/magic_enum) is used to simplify usage of enums in C++. It provides iteration over enums, convertion to strings etc.
* [pugixml](https://github.com/zeux/pugixml) is used to parse xml data.
* [simdutf](https://github.com/simdutf/simdutf) is used to work with UTF-8 encoded strings.
* [spdlog](https://github.com/gabime/spdlog) is used for logging.
* [tomlplusplus](https://github.com/marzer/tomlplusplus) is used to parse [TOML](https://toml.io/en/) configuration files.
* [Boost.filesystem](https://github.com/boostorg/filesystem) is used to check portability of file names. This functionality is not present in C++ standard filesystem library.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<a name="#code-structure"></a>

## Code structure
The apllication has [MVC](https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller) architecture. The code is divided into 4 directories:
1. CLI:
    - TApplicationCLI - class responsible for providing CLI interface to the user.
2. Controllers:
    - TController - singleton class that provides functionality to send the message to data provider thread. It also contains UI container and starts the provider thread.
    - TConfig - singleton class responsible for validation of config values.
    - NSProvider - namespace which provides functionality of sending requests to the NBU API and fetching data from it.
    - NNFileType - enum of output file format.
    - NAMessages - a collection of messages that can be sent to the provider thread.
3. Models:
    - ACurrencyData - a collection of type aliases for the currency data.
4. Views is the directory for TUI classes:
    - TCurrencyDataView - a text representation of currency data.
    - TCurrencyTable - a view to represent all currency data as a table.
    - TIntervalModal - a modal form that is responsible for the validation of the interval the user inputted.
    - TToggle - a toggle button class. It used to switch between the output file formats.
    - TUIContainer - a class that represent the whole user interface.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Contact



Serhii Panchenko - [@sideshowbobgot](https://t.me/sideshowbobgot) - sideshowbobgot@gmail.com

Project Link: [https://github.com/SideShowBoBGOT/NBUCurrencyTracker](https://github.com/SideShowBoBGOT/NBUCurrencyTracker)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## License
This project is licensed under the [MIT License](https://mit-license.org/).

<p align="right">(<a href="#readme-top">back to top</a>)</p>