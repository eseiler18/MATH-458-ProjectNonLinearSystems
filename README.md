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

# How to use
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
Only when we use a external cpp for the function.

## Your turn to test 
You can now use this csv file to put your own function. If you want to use your own csv, put it in the folder /build/project and launch the main_louis with the file name on argument. The simpliest way is to clear our exemple in the data.csv and use it for your test as the main_louis will use this file by default if it has any argument.
Note that lauch the main_louis will always read all the lignes and resolve for all the function in the CSV.

## A note on the other main and Linear system
You have maybe already see the other excecutable code, It represent our extension of our project : Solving system with newton Method. <br/>
This branch is actually in working and we have only implement the method with a quick exemple directly in the cpp file. 
We have the way to represent the function and jacobien matrice but we only lack a interface (like the csv file) to run fifferent exemple without remake the project.
You can therefore run:
  	```
	./runSystem
	```
and it will resolve the systeme :<br/>
f1 = x0^2+x0*x1-10<br/>
f2 = x1+3*x0*x1^2-57

# Implementation
The resolution of the equation is done with two main steps, the reading phase, and the solving phase.
## Reader
Classes used to read the csv are in the [Project/ReadData](https://github.com/eseiler18/MATH-458-ProjectNonLinearSystems/tree/main/project/readData) folder, the main class is **ReaderData**. The role of this object is to read each row of the csv file to create **Data** structures (see [data.h](https://github.com/eseiler18/MATH-458-ProjectNonLinearSystems/tree/main/project/readData/parser/Data.h) which contain parameters of the numerical methods input by the user.
The interesting aspects of the implementation concern the reading of functions (the equation and its derivative column 2 and 3 of the csvfile). The **AbstractInterpreterFunction** is a common interface which contain a pure virtual method _createExecutableFunction_. There are two way inputting the desire functions, from its mathematical expression or with C++ code in an external file. Each have a class which inherit from **AbstractInterpreterFunction** and the _createExecutbaleFunction_ method return an **AbstractNode** object (explain later) which is the executable function
### From mathematical expression
Classes used to interpret function from expression are in the folder Project/ReadData/Parser.
The following diagram explain the process passing from an expression to an executable function for the mathematic expression “x+3x^2*5”.
![Parser](/figure/figParser.png "Parser")
First there is the reading phase of the expression done by the _readTokens_ method of the **Parser** class which attribute to each character a token. A token is the representation of a character or a group of character with a certain token type (see TokenType.h) there are create from an **AbstractToken** class.
Then the _normalizeAndVerifyTokens_ method of the **Parser** class manage implicit operation, verify the validity of each token, and manage operation priorities by adding implicit parentheses.
![Builder](/figure/figBuilder.png "Builder")
Finally, there is the building phase of the executable function from tokens done by the _build_ method of the **Builder** class. The executable function is built in the form of a binary tree with operator as node and number, variables, and function as leaf. 
Nodes are created from the **AbstractNode** class which contain a pure virtual method _solve_. Operator, variable, number, and functions node have a class that inherit from **AbstractNode**. In each class the _solve_ method access the value of the node for a certain double x. Then we can access the value of the function for all x calling the _solve_ method on the root **AbstractNode** of the tree and it recursively calls _solve_ method of each node to compute the result (note that the tree is built only one time at reading step).  
### From c++ code
Accessing the function from c ++ code is much easier since the function is already built and can be interpreted by the program. To recover the function from an extern cpp file we dynamically compile it with the _system_ command and create a library in the /tmp folder. The library is load and a function pointer is created from the name of the function in the cppfile. Then an **ExternalFunctionNode** which inherit of **AbstractNode** is created to fit with the common interface **AbstractInterpreterFunction** (a tree is built with just one vertex and value of the function can be access with the _solve_ method of **AbstractNode**).
## Solver
All classes concerning solving step can be found in the folder project/solverMethods.
After the reading step, information about the equation and the numerical methods are stored in a structure **Data** (see data.h).
The equation is solved from an **AbstractSolveur** class which contain common element of all numerical methods (equation, tolerance, number of maximum iterations) and a pure virtual method call _SolveEquation_. Then the four methods implemented have an associated class which inherits from **AbstractSolver**.  Numerical methods are implemented in the _SolveEquation_ method of each child class and return the result or an exception if the method didn’t converge.
A little word on the **NewtonSystem** class which is implemented to solve system with several variable (does not inherit from **AbstractSolveur**). The eigen library is used to create a vector and a matrix of **AbstractNode** which correspond to equations and the Jacobian of the system.
# Validating Test
## What we Testing
All the test are on the test1.cpp file you can found on google_test folder.
Two fixture are implement, and each one correspond to a different part of the project. SetUp is implement in each one to facilitate the Test.
### Testing the Parseur
This correspond to the fixture Fixture_Interpreter. The goal is to tcheck all the corner case of our parseur and verify if it can reconstruct the desired fonction.
For this case, we compare the constructed function with the reel one, and assert if our parser can actually :<br/>
- can make simple operation ( + ; - ; * ; / )
- respect the priority of operation
- respect the ( ) priority
- recognise the externed function we have implemented like cos, exp etc ...
- handle with the multi-variable function ( x0, x1 etc ...)

We also assert than our parseur throw the desired error when it detect a incoherence :
- begin with a operator + ; * or /
- operator follow by another operator : ( 5 + * 4), same with number ( 2 3 +4)
- non recognise external function : ( skz(x) )
- a coma not open or not close : 3*4x )

### Testing the Method
This correspond to the fixture Fixture_Solve.<br/>
We actually test if the method work correctly.
---> parlez des test simple qui converge.  
---> parlez des Test exeption qui diverge
---> parlez des differntes erreurs qui sont trhow, par exemple les erreur liée au parseur sont differentes des erreurs liées a la divergence du method
--->> Bisection : std:: invalid argument pour f(a)*f(b) >0 mais differnts pour iterate

# Limitation and perspective
## More way to input functions:
For the moment our project allows the user to input functions with a mathematical expression or a c++ code. But we have good reason to think that the user wants to input other type for example tabular functions. Then to implement we must create a class **InterpreterTablular** which inherit of **AbstractInterpreterFunction** with the file in parameter. Then the _createExecutableFunction_ method of this class must analyse the content of the file and return an **AbstractNode** which is the executable function. 

## Finish System Implementation:
The extension to system solver isn’t finish yet. As you can see in the main.cpp file the solving part is implemented and work with mathematical expression (thanks to the eigen library). But the reading part isn’t implemented yet the user can’t give his own system (if you want to test you can change the example in main.cpp but you need to recompile). However, the parser work with several variable (x0, x1, x2…) and the _solve_ method of **AbstractNode** is polymorphize with several variable input to access value of multi variable functions.
