# MATH-458 - Programming Concepts in Scientific Computing

Project of the PSCS course at EPFL given at EPFL Fall 2021. 

## Team members

- Emilien Seiler
- Louis Le Guillouzic

## Project 3: Non-linear systems

Implementation of numerical methods for the solution of nonlinear equations.  
For a function f , find x such that : _f (x) = 0_

Mandatory: consider a scalar nonlinear problem and implement the
bisection, aitken, chord, newton and fixed point methods.

Optional: Extension to systems of nonlinear equations solved by the Newton and/or
modified Newton method.

## Sources

Sources: [here](https://onlinelibrary.wiley.com/doi/pdf/10.1002/9781118673515.app8) for the Newton’s, chord and bisection method, and [here](https://mat.iitm.ac.in/home/sryedida/public_html/caimna/transcendental/iteration%20methods/fixed-point/iteration.html) for
the fixed point method. [Here](https://en.wikipedia.org/wiki/Aitken%27s_delta-squared_process) for the Aitken acceleration to be applied to
these methods.

# How to use ... (LOUIS)
## Make & run 
To make this project, you need to have the linux tool "cmake".
Go to the root of the git after cloning :
  	```
	cd  MATH-458-ProjectNonLinearSystems
	```
	
In order to compile it you should first install *googletest* and *eigen*.
You can run this line of code to place them in their respectif place.
	
	git submodule update --init 
	
  Then, building is done as usual, in the terminal:
	
	mkdir build
	cd build
	cmake ..
	make
	
 The Build is complet ! You can in a first time Run the Test to tcheck if everything is ok !
 	
	cd google_test
	./Google_Tests_run
	
 Normally, you should pass the 17 Test. They tcheck all the functionnality of your project. We will detay more about them below.
 We can know test the default main, to compute some function. We just need to go to the project repository :

  	
	cd ..
	cd projet
	
To better understand this project, take a look on "data.csv" file. 
(Important : the semicolon separator must be desactived, but the coma separator must be actived)
If you have "gopen" on linux you can use :
  	```
	gopen data.csv
	```
	
If you are a looser on windows like Emilien, you can go to your file and open data.csv in "MATH-458-ProjectNonLinearSystems/build/project" folder. You will see the different exemple of function our project can handle, and the parameters you can input. Now lauch the main with no argument : it will take the "data.csv" file in input by default :
	
	./main_louis

Look the Answer on the terminal :<br/>
-First the warnings : They tell missing or incoherent element in the csv <br/>
-Next the solutions find by the method. Note that the first column in the csv indicate the method you want to use, so it's normal that some function are resolved by only one method.
	
## Test your function : how to fill the csv
### first column : Choose your method 
empty -> All the method <br/>
n for newton; b for Bisection; c for Classic Chord; f for Fixed Point method <br/>
Note that the letter must be separated by a semicolon ";"
### 2nd column : Choose the function 
 #### First option (simple function)  :
 Write the function in the column. Use x as variable. You can use ^ for power. You can use external function :  
 	
	exp(..) log(..) sqrt(..) cos(..) sin(..) tan(..) atan(..)

 #### 2nd option : Use another cpp file  :
 Put the name of the function as it appears in the cpp file. You should also fill the 9th column by adding the Name of the cpp file.<br/>
 The function file have to be in the same folder than the CSV File. Be carreful that the different function have to be inclueded in a extern "C" {}
 
 	extern "C" {
		double nameFuncion(double x){return 2*x;}
	}
The simpliest way is to use the "function.cpp" file at disposition in "/build/project/" and copy/paste the function you want to test. 

### 3th column : Fill the derivative function 
If you want to use the Newton method, you need to fill the explicit derivative of the function. You can choose the two way explained just before. 
Note that for the 2nd way, the function and derivative function have to be in the same cpp file.
You can let this column empty if you doen't want to use de Newton method. <br/>
### 4th and 5th column : Bounds   
It's the lower and upped bound for the Bisection. You can let this empty if you doesn't want to use this method.
### 6th Column : Initial Value
The initial value for Chord, Newton and fixed point. You can let this empty if you doesn't want to use this methods.
### 7th Column : tolerance
The exactness you want to reach with the method. If you let this empty, the tolerance will be set by default at 0.000001. A warning message will also be print in the terminal.
### 8th Column : Max iteration
The max number of step you will allow before stop the method. If you let this empty, the Max iteration will be set by default at 10000. A warning message will also be print in the terminal.
### 9th Column : External file name
see 2th column for another cpp file

## Your turn to test 
You can now use this csv file to put your own function. If you want to use your own csv, put it in the folder /build/project and launch the main_louis with the file name on argument. The simpliest way is to clear our exemple in the data.csv and use it for your test as the main_louis will use this file by default if it has any argument.
Note that lauch the main_louis will always read all the lignes and resolve for all the function in the CSV.

## A note on the other main and Linear system
You have maybe already see the other excecutable code, It represent our extension of our project : Solving system with newton Method. <br/>
This branch is actually in working and we have only implement the method with a quick exemple directly in the cpp file. 
We have the way to represent the function and jacobien matrice but we only lack a interface (like the csv file) to run fifferent exemple without remake the project.
You can therefore run:
  	```
	./main
	```
and it will resolve the systeme :<br/>
f1 = x0^2+x0*x1-10<br/>
f2 = x1+3*x0*x1^2-57

# Implementation (EMILIEN)
## Reader
## Solver
# Validating Test ... (LOUIS)
## What we Testing
All the test are on the test1.cpp file you can found on google_test folder.
### Testing the Parseur (=decodeur)
This correspond to the fixture Fixture_Interpreter. The goal is to tcheck all the corner case of our parseur and verify if it can reconstruct the desired fonction.
For this case, we compare the constructed function with the reel one, and assert if ou parser actually :<br/>
- can make simple operation ( + ; - ; * ; / )
- respect the priority of operation
- respect the ( ) priority
- recognise the externed function we have implemented like cos, exp etc ...
- handle with the multi-variable function ( x0, x1 etc ...)


# Limitation Perspective (EMILIEN)
