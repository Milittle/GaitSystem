# Project GaitSystem

Project GaitSystem is an Gait recognition system based Windows Visual Studio 2017. The algorithm based the paper  [Gait optical flow image decomposition for human recognition](https://ieeexplore.ieee.org/document/7560427). 

>As a behavioral biometric, gait recognition has gained an increased interest in recent years because it can operates without subject cooperation and from a distance. This paper present a novel gait feature extracting approach based on gait optical flow image(GOFI)decomposition.

I use this method implment the Project based C++, Qt and some 3rdparty to recognition the [GaitDatasetB-silh](http://www.cbsr.ia.ac.cn/users/szheng/?page_id=71). It's just use the silhouettes image and the angle fixed the 90 degree.

## Table of Content

- [Project GaitSystem](#project-gaitsystem)
  - [Table of Content](#table-of-content)
  - [Prerequisites](#prerequisites)
  - [Getting the code](#getting-the-code)
  - [Getting the Datasets](#getting-the-datasets)
  - [Running this Project with you](#running-this-project-with-you)
  - [Gif Demo](#gif-demo)
- [Concat Getting Help](#concat-getting-help)
- [Ref:](#ref)

## Prerequisites

* Qt
* armadillo-8.200.2[DOWNLOAD LINK](http://arma.sourceforge.net/download.html)
  * you can download this library through above link or use my project 3rdparty dependences.
* opencv3.1 [DOWNLOAD LINK](https://sourceforge.net/projects/opencvlibrary/files/opencv-win/3.1.0/opencv-3.1.0.exe/download)
* Also you need the vs 2017
* The testing Dataset(GaitDatasetB)

## Getting the code

You can use the git tool to clone this project. through:

```shell
git clone git@github.com:Milittle/GaitSystem.git
```

## Getting the Datasets

1. Using this link to download the silhouettes [GaitDatasetB](http://www.cbsr.ia.ac.cn/GaitDatasetB-silh.zip)
2. Using the unzip software unzip the Dataset.

## Running this Project with you

1. Needing config the Qt library.
2. Opening the project .sln file, you will look the Project structure. Fllowing:

![Project Structure](https://s1.ax1x.com/2018/10/17/idTj8f.png)

2. You can use `Crtl + F5` run the project.
3. you will see the following Figure:

![UI](https://s1.ax1x.com/2018/10/17/id79bj.png)

**Load Model---:** Load the gait silhouettes sequence from the Dataset B.

**Add To DataBase---:** Using this button add the gait feature to the Database(Feature database).

**Recognition---:** Using this button recognition the people already loaded.

**Delete DataBase---:** The button feature is not implement.(i will add it).

**DataBase Count---:** This will show the Database people's count.

**RecognitionOBJ---:** This will show the Recognitioned People's if you click the Recognition button after.

## Gif Demo

![DemoGif](https://s1.ax1x.com/2018/10/17/id7fds.gif)

# Concat Getting Help

**Email:** mizeshuang@gmail.com

**Author:** Milittle

最后：这是我写的比较水的一个步态识别的小Demo，以后再有机会做一些其他方面的工作。

毕竟这是第一个步态识别小Demo，留作纪念而已。（好多东西都需要优化！！！）

# Ref:

About **Armadillo** **Library**:

Conrad Sanderson and Ryan Curtin. 
*Armadillo: a template-based C++ library for linear algebra*. 
[Journal of Open Source Software, Vol. 1, pp. 26, 2016. ](http://arma.sourceforge.net/armadillo_joss_2016.pdf)

Conrad Sanderson and Ryan Curtin. 
*A User-Friendly Hybrid Sparse Matrix Class in C++*. 
[Lecture Notes in Computer Science (LNCS), Vol. 10931, pp. 422-430, 2018. ](http://arma.sourceforge.net/arma_spmat_icms_2018.pdf)

