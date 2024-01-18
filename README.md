# NBUCurrencyTracker
<a name="readme-top"></a>

NBUCurrencyTracker is an application in C++ to fetch currency 
rates using data from the National Bank of Ukraine (NBU) API.

![Screenshot](Docs/Screenshot%20from%202024-01-18%2009-20-29.png)

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [External libraries](#externallibs)
- [License](#license)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Installation
1. Clone the repository:
```sh
git clone https://github.com/SideShowBoBGOT/NBUCurrencyTracker
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

![Screenshot](Docs/Screenshot%20from%202024-01-18%2009-20-29.png)
![Screenshot](Docs/Screenshot%20from%202024-01-18%2010-45-11.png)

### Error messages

If any issues encountered while trying to fetch the data from the API or save it to the file, a corresponding message appears:

![Screenshot](Docs/Screenshot%20from%202024-01-18%2010-49-14.png)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## External libraries




