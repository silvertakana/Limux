# Lumix Game Engine

Author - [@Silvertakana](https://github.com/silvertakana) | [GitHub](https://github.com/silvertakana) | [Discord](https://discord.gg/Acj88TtQ)

* Started on Apr 24, 2022

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

Lumix Engine is a game engine supports both 2D and 3D rendering. It is currently free to use and modify. it can be use in high production applications other than games. 

Installation
============

* ### Getting Started

	

* ### Installing
	Note: At this point, MacOS and Linux are not supported.
	* #### Windows 
		* step 1: Run these command in your chosen command-line environment
			```
			git clone --recursive https://github.com/silvertakana/Lumix.git
			cd Lumix
			setup.bat vs2022
			```
			you must provide an editor to `setup.bat` for it to correctly build the project. in this case, I used `vs2022` (visual studio 2022.)
    	* step 2: find the solution file and run it. e.g. `Lumix.sln`

Usage
=====
* ### Creating a new application

	Lumix uses a layer base execution order system. So most of your codes will be in these layers. This is so that when you have unrelated things(e.g. UI, Physics, etc.) and want to separate them so that they can't affect each other, you can use these layers. The application will join these layer together and execute them in order.

	```c++
	#include <Lumix.h>

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
