#include "texture.h"
#include <QDebug>
#include <fstream>
#include <QPixmap>
#include <QImage>




texture::texture(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(readImage()));
    connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(savePointCloudData()));
}

texture::~texture()
{

}

void texture::readImage()
{
    image = cv::imread("C:/Users/SVT/Desktop/bharath/data set for texture mapping/PCL_idol_image_Color.png");
    if (image.empty()) {
   
        return;
    }

    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    QImage qImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(qImage);
    ui.label->setPixmap(pixmap.scaled(ui.label->size(), Qt::KeepAspectRatio));
    ui.label->setScaledContents(true);
}

void texture::readPointCloudData()
{

    // reading a pointcloud data 
    pointCloud = cv::Mat::zeros(0, 3, CV_64FC1);
    std::ifstream infile("C:/Users/SVT/Desktop/bharath/data set for texture mapping/PCL_Idol.txt");
    if (!infile.is_open()) {
       // if file is not opened do nothing!!    
        return;
    }
    double x, y, z;
    while (infile >> x >> y >> z) {
        cv::Mat point(1, 3, CV_64FC1);// point=create the 1 row and  3 coloum
        point.at<double>(0, 0) = x;
        point.at<double>(0, 1) = y;
        point.at<double>(0, 2) = z;
        pointCloud.push_back(point);
    }
    infile.close();
}

void texture::mapColorToPointCloud()
{

//function call Readimage and  ReadpointcloudData to loadimage and the pointcloud

    readImage();
    readPointCloudData();

    // Define the camera calibration matrix K
    cv::Mat K = (cv::Mat_<double>(3, 3) << 4.6839e+03, 0, 1.2258e+03, 0, 4.6833e+03, 983.6679, 0, 0, 1);

    // Resize the pointCloudColors vector to match the number
    //--of points in the point cloud
    pointCloudColors.resize(pointCloud.rows);//The colour pointcloud rows will 
                                             //--get resized to pointcloud data

    // Iterate over each point in the point cloud
    for (int i = 0; i < pointCloud.rows; i++) {
   // Retrieve the 3D coordinates of the point and assigned to x,y,z
        double x = pointCloud.at<double>(i, 0);
        double y = pointCloud.at<double>(i, 1);
        double z = pointCloud.at<double>(i, 2);

        // Project the 3D point to the image plane using the camera calibration parameters
        cv::Mat point3D = (cv::Mat_<double>(1, 3) << x, y, z);//assigning x,y,z to point3d
        cv::Mat projected_point; 
        cv::projectPoints(point3D, cv::Mat::eye(3, 3, CV_64FC1), cv::Mat::zeros(1, 3, CV_64FC1), K, cv::noArray(), projected_point);
        //project the 3d points to the image plane ^ 
        // Retrieve the projected 2D coordinates        
        int u = std::round(projected_point.at<cv::Vec2d>(0)[0]);
        // round is used to roundup the decimal value to the nearest integer 
        int v = std::round(projected_point.at<cv::Vec2d>(0)[1]);


        if (u >= 0 && u < image.cols && v >= 0 && v < image.rows)
        // u >= 0: Checks if the projected x-coordinate (u)
        //is greater than or equal to 0.
        //so that the point is not projected outside the left boundary of the image.
        //if u < image.cols point is not projected outside the right boundary of the image.
        
        {         
            cv::Vec3b color = image.at<cv::Vec3b>(v, u);
            color = cv::Vec3b(color[2], color[1], color[0]);            
            //clor = cv::Vec3b(color[2], color[1], color[0]); 
            //are used to retrieve the color value of a pixel from the image at 
            //the projected 2D coordinate (u, v) and convert it to the RGB color format.
            // This line accesses the pixel at the coordinates (u, v) in the image 
            // and retrieves its color 
            //value. cv::Vec3b represents a 3-channel (BGR) color vector in OpenCV. 
            //color = cv::Vec3b(color[2], color[1], color[0]);: 
            // By default, OpenCV uses the BGR color format to represent images.
            //  in some cases, RGB format is preferred. 
            //  swaps the channels of the color vector color from BGR to RGB format
            pointCloudColors[i] = color;
        }
        else {
         
            pointCloudColors[i] = cv::Vec3b(0, 0, 0);
        }
    }
}





void texture::savePointCloudData()
{
    // Map color to point cloud
    mapColorToPointCloud();

    // Open the output file
    std::ofstream outfile("C:/Users/SVT/Desktop/bharath/texture01.ply");
    if (!outfile.is_open()) {
        qDebug() << "Failed to open output file";
        return;
    }

    // Write the PLY header
    outfile << "ply\nformat ascii 1.0\n";
    outfile << "element vertex " << pointCloud.rows << "\n";
    outfile << "property float x\n";
    outfile << "property float y\n";
    outfile << "property float z\n";
    outfile << "property uchar red\n";
    outfile << "property uchar green\n";
    outfile << "property uchar blue\n";
    outfile << "end_header\n";

    // Write the point cloud data
    for (int i = 0; i < pointCloud.rows; i++) {
        cv::Mat point = pointCloud.row(i);
        outfile << point.at<double>(0, 0) << " " << point.at<double>(0, 1) << " " << point.at<double>(0, 2);
        outfile << " " << static_cast<int>(pointCloudColors[i][2]) << " " << static_cast<int>(pointCloudColors[i][1]) << " " << static_cast<int>(pointCloudColors[i][0]) << "\n";
    }
    outfile.close();
}