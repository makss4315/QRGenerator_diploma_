# QR Code Generator (C++ Desktop Application)

## 📌 Project Overview
This project is a desktop application for generating QR codes, implemented in C++ using the Qt framework and OpenCV library.



- Generate QR codes from text input

- Decode QR codes from images

- Save generated QR codes as PNG files

- Store history of the last 10 generated QR codes in a JSON file

- Use a modern graphical user interface (GUI)

---

## 🛠 Technologies Used

- C++17
- Qt (GUI)
- OpenCV (image processing & PNG saving)
- CMake (build system)
- JSON (for storing generation history)

---

## 📂 Project Structure

- UI/ -> Graphical user interface components
- core/ -> Core QR generation logic
- CMakeLists.txt -> Build configuration


---


## 💾 Data Storage

- Generated QR codes are saved locally as PNG files in the user's temporary directory.
- Metadata of the last 10 generated QR codes is stored in a JSON file.
---
## ⚙️ Installation & Configuration
###  Install Qt

- Download and install Qt 6 (MinGW version) from:

```
https://www.qt.io/download 
```

Make sure you install:

- Qt 6.x

### MinGW 64-bit compiler

- After installation, note your Qt installation path, for example:

```
C:/QT/6.10.1/mingw_64/lib/cmake/Qt6 
```
---
##  Install OpenCV (MinGW Build)

- This project uses prebuilt OpenCV binaries for MinGW:
```
https://github.com/huihut/OpenCV-MinGW-Build
```
### Steps:

- Download the latest release

- Extract it to a directory, for example:

```
C:/Libraries/OpenCV-MinGW
```
- Remember this path — you will need it for CMake configuration.
---
## Modify CMakeLists.txt

- Before building the project, you must update the following lines in CMakeLists.txt:

```
set(Qt6_DIR "X:/QT/6.10.1/mingw_64/lib/cmake/Qt6")  
set(OpenCV_ROOT "X:/Git_Repo/OpenCV-MinGW")         
```


## ⚙️ How to Build


### Build Steps:

```bash
mkdir build
cd build
cmake ..
cmake --build 
```
---
## 📦 Deployment (Running the Application)

After building, the executable requires Qt and OpenCV DLL files.
Qt Deployment

- Run:

```
windeployqt QRGenerator.exe
```
This will automatically copy required Qt DLLs.

## OpenCV DLL

You must manually copy the required OpenCV DLL (e.g. opencv_world4xx.dll)
from your OpenCV installation directory into the same folder as the executable.

## 📦 Prebuilt Release

- A ready-to-run Windows version is available in the Releases section.

```
Download → Extract → Run QRGenerator.exe
```
All required Qt and OpenCV DLLs are included.
