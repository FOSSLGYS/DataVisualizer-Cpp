# DataVisualizer-Cpp

####Project Description

Data visualizer is a QT/C++ based application designed to give a visual representation of various data structures, currently, stack, queue, and binary min heap. It provides an easy to add framework so that additional data structuress may be added in future.

####Tools and Technology

The project has been developed in QT Creator IDE, using C++ based QGraphics framework for GUI elements. Specific instructions on how to download, setup and run using QT creator are present in the [Instructions Wiki](https://github.com/GHCFOSS/DataVisualizer-Cpp/wiki).

####The Repository Details

The "DataVisualizer" folder contains all the source, UI and header files. This folder can be opened as a project in "QT creator" IDE. 

The project's design organizes into the following components.

#####Datastructure Component

Every datastructure type (DS) to be visualized has a UI file, CPP source file and a header file with a class definition. Common interface APIs have been added for every DST such as insert/remove/clear/cleanup. These APIs have the implementation required for displaying a specific DST. 

#####Display Component

Display types such as list (used in queue and stack DSes) and tree (used in min Heap and BST DSes) have been abstracted and defined in the visualizer header and cpp files.

#####Main GUI

Top level GUI source/UI is handled in files titled "main".

####How to work on an Issue

You can view the open issues for the repository under [Issues](https://github.com/GHCFOSS/DataVisualizer-Cpp/issues). If there is a particular existing issue that you would like to fix, please leave a comment below it with intent and details of how you intend to fix it. This will reduce duplication of effort.If you would like to propose an enhancement, or report a bug that you would like to work on, feel free to open new issues and we will assign them to you.

####How to get help

Have questions, comments, feedback or looking for help? We are available and can be reached at the Slack channel created specifically for this project. IRC channels are so a thing of the past! If you are having trouble signing up, you can reach us at ghcfoss@gmail.com for signup help.
