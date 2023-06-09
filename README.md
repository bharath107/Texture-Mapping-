![Capture](https://github.com/bharath107/Texture-Mapping-/assets/61610825/53448138-1ced-43f7-866c-180358a71d8e)
![Capture1](https://github.com/bharath107/Texture-Mapping-/assets/61610825/1775aa64-80fc-4d41-aec5-05404a5eb968)
![Capture2](https://github.com/bharath107/Texture-Mapping-/assets/61610825/3d267733-b4d5-4ae7-9448-f437ec1e21af)
![Capture3](https://github.com/bharath107/Texture-Mapping-/assets/61610825/dd2797e4-5db2-4316-afe2-d1e916a7f1fd)
![Capture4](https://github.com/bharath107/Texture-Mapping-/assets/61610825/07e3a8dd-f11a-4b77-b838-09c3d6e18f33)
![PCL_idol_image_Color](https://github.com/bharath107/Texture-Mapping-/assets/61610825/a097b7e7-8490-48ce-8043-f66498afab0a)
# Texture-Mapping-
Texture Mapping with Point Cloud and Image
This project implements a texture mapping technique that associates color information from an image with a 3D point cloud. The code takes as input a point cloud data file and 
and image file, and generates a new point cloud file with RGB color information mapped onto each point. The resulting point cloud can be visualized with color in 3D rendering 
software or used for further analysis.

Features:-
Read an image file and display it on a graphical user interface (GUI)
Read a point cloud data file and store the 3D coordinates
Project each point onto the image plane using camera calibration parameters
Extract the RGB color values from the image at the projected 2D coordinates
Map the color information to each corresponding point in the point cloud
Save the mapped point cloud data in the PLY file format

Usage:-
Run the program and open the GUI.
Click the "Read Image" button and select an image file to display it on the GUI.
Click the "Read Point Cloud" button and select a point cloud data file.
The program will project each point onto the image plane and map the corresponding color information.
The GUI will display the mapped image with color and the 3D point cloud.
Click the "Save Point Cloud" button to save the mapped point cloud data in a PLY file.

Dependencies:-
OpenCV: Required for image processing and camera calibration functions.
Qt: Required for the graphical user interface components.
C++ STL: Standard Template Library for file I/O and data manipulation.

Installation:-
Clone or download the repository to your local machine.
Install the required dependencies (OpenCV and Qt) according to their respective documentation.
Build the code using a C++ compiler with support for C++11 or later.
Run the executable file to launch the program.

This image shows an example of the texture mapping result. The point cloud data is mapped with color information from the image, creating a visually enhanced representation of the 3D scene.
