<<<<<<< HEAD
# Welcome to Limux Game Engine
=======
# Lumix Game Engine
>>>>>>> 5b95b19c54b3dbd73c4028756609e5ad568466b1

Author - [@Silvertakana](https://github.com/silvertakana) | [GitHub](https://github.com/silvertakana) | [Discord](https://discord.gg/Acj88TtQ)

* Started on Apr 24, 2022


<<<<<<< HEAD
![Limux Logo](res/LimuxLogo.png)
=======
<img src="res/LumixLogo.svg" alt="Lumix Logo" width="256"/>
>>>>>>> 5b95b19c54b3dbd73c4028756609e5ad568466b1

# Table of Contents

* [Introduction](#introduction)
* [Installation](#installation)
  * [Getting Started](#getting-started)
  * [Installing](#installing)
* [Usage](#usage)
  * [Creating a new application](#creating-a-new-application)
  * [Running the application](#running-the-application)
  * [Testing the application](#testing-the-application)
* [Features](#features)
  * [Completed](#completed)
  * [In Development](#in-development)
  * [Planned](#planned)
* [Deployment](#deployment)
  * [Deploying the application](#deploying-the-application)
* [Libraries](#libraries)
* [Licenses](#licenses)
  * [Main License](#main-license)
  * [Library Licenses](#library-licenses)
* [Contributing](#contributing)

* [Extra Stuff](#extra-stuff)
  * [Future Plans](#future-plans)
  * [FAQ](#faq)
  * [Support](#support)
  * [Acknowledgements](#acknowledgements)
  * [Credits](#credits)
  * [Contact](#contact)

Introduction
============

<<<<<<< HEAD
Limux Engine is a game engine supports both 2D and 3D rendering. It is currently free to use and modify. it can be use in high production applications other than games. 
=======
Lumix Engine is a game engine supports both 2D and 3D rendering. It is currently free to use and modify. it can be use in high production applications other than games. 
>>>>>>> 5b95b19c54b3dbd73c4028756609e5ad568466b1

Installation
============

* ### Getting Started

	

* ### Installing
	Note: At this point, MacOS and Linux are not supported.
	* #### Windows 
		* step 1: Run these command in your chosen command-line environment
<<<<<<< HEAD
			```batch
			git clone --recursive https://github.com/silvertakana/Limux.git
			cd Limux
			setup.bat vs2022
			```
			you must provide an editor to `setup.bat` for it to correctly build the project. in this case, I used `vs2022` (visual studio 2022.)
		* step 2: find the solution file and run it. e.g. `Limux.sln`
=======
			```
			git clone --recursive https://github.com/silvertakana/Lumix.git
			cd Lumix
			setup.bat vs2022
			```
			you must provide an editor to `setup.bat` for it to correctly build the project. in this case, I used `vs2022` (visual studio 2022.)
    	* step 2: find the solution file and run it. e.g. `Lumix.sln`
>>>>>>> 5b95b19c54b3dbd73c4028756609e5ad568466b1

Usage
=====
* ### Creating a new application

<<<<<<< HEAD
	Limux uses a layer base execution order system. So most of your codes will be in these layers. This is so that when you have unrelated things(e.g. UI, Physics, etc.) and want to separate them so that they can't affect each other, you can use these layers. The application will join these layer together and execute them in order.

	```c++
	#include <Limux.h>
=======
	Lumix uses a layer base execution order system. So most of your codes will be in these layers. This is so that when you have unrelated things(e.g. UI, Physics, etc.) and want to separate them so that they can't affect each other, you can use these layers. The application will join these layer together and execute them in order.

	```c++
	#include <Lumix.h>
>>>>>>> 5b95b19c54b3dbd73c4028756609e5ad568466b1

	class DemoLayer : public LMX::Layer
	{
	public:
		DemoLayer()
			:Layer("DemoLayer") // Debug name
		{}
		virtual void OnAttach() // Called when the layer is attached to the application
		{
			LMX_INFO("Started Demo Layer");
		}
		virtual void OnDetach() // Called when the layer is detached from the application
		{
			LMX_INFO("Stopped Demo Layer");
		}
		virtual void OnUpdate(LMX::Timestep ts) // Called when the layer is detached from the application
		{
			LMX_INFO("Updated Demo Layer");
		}
		virtual void OnEvent(LMX::Event& event) // Called when the layer is detached from the application
		{
			LMX_INFO("{0}", event.ToString());
		}
	};
	class DemoApp : public LMX::Application
	{
	public:
		DemoApp()
		{
			PushLayer(new DemoLayer()); // Add the layer to the execution stack each one will be executed in order
		}
		~DemoApp()
		{}
	};
	```
* ### Running-the-application
	you must include the following at the bottom of your `cpp` file.

	```c++
	LMX::Application* LMX::CreateApplication()
	{
		return new DemoApp(); // telling the engine what Application to use
	}
	```
	change `DemoApp` to your application name.
<<<<<<< HEAD

Libraries
=========

* [Assimp](https://github.com/assimp/assimp).
* [GLFW3](https://github.com/glfw/glfw).
* [ImGUI](https://github.com/ocornut/imgui).

Licenses
=======

* ### Main License

	* [Limux License](LICENSE)

* ### Library Licenses

	* [Assimp License](https://github.com/assimp/assimp/blob/master/LICENSE).
	* [GLFW3 License](https://github.com/glfw/glfw/blob/master/LICENSE.md).
	* [ImGUI License](https://github.com/ocornut/imgui/blob/master/LICENSE.txt).

Contributing
============
* [@Silvertakana](https://github.com/silvertakana)

Extra Stuff
==========

* ## Future Plans

	  To be written.

* ## FAQ

	  To be written.  

* ## Support

	  To be written.

* ## Acknowledgements

	  To be written.

* ## Credits

	  To be written.

* ## Contact

	  To be written.
=======
>>>>>>> 5b95b19c54b3dbd73c4028756609e5ad568466b1
