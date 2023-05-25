// texture.h
#ifndef TEXTURE_H
#define TEXTURE_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include "ui_texture.h"

class texture : public QMainWindow
{
	Q_OBJECT

public:
	texture(QWidget* parent = nullptr);
	~texture();
public:
	cv::Mat pointCloud;
	std::vector<cv::Vec3b> pointCloudColors;

private:
	Ui::textureClass ui;
	cv::Mat image_;
	std::vector<cv::Vec3f> point_cloud_data_;
	cv::Mat image;  


private slots:
	void readImage();
	void readPointCloudData();
	//void colorThresholding();
	void mapColorToPointCloud();
	void savePointCloudData();
	//void visualizePointCloud();
};
#endif // TEXTURE_H
