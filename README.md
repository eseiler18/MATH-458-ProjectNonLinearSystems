# MATH-458 - Programming Concepts in Scientific Computing

Project of the PSCS course at EPFL given at Fall 2021. 
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
#### Requierement
* linux tool "cmake".
* python3 (for eigen)
* g++ <br/>

After cloning go to the root of the git:
  	```
	cd  MATH-458-ProjectNonLinearSystems
	```

### Build the project

In order to compile you should first install **googletest** and **eigen**.
	
	git submodule update --init 
	
Then, building is done as usual, in the terminal:
	
	mkdir build
	cd build
	cmake ..
	make
	
 The Build is complet ! You can in a first time Run the Test to check if everything work!
 	
	cd google_test
	./Google_Tests_run
	
 Normally, you should pass all tests. They check all the functionnality of the project.<br/>
 We can now test the main, to solve some equations. Go to the project repository :

  	
	cd ../projet
	
To better understand this project, take a look on "data.csv" file. 
If you have "gopen" on linux you can use :
  	```
	gopen data.csv
	```
.Otherwise open **data.csv** in _MATH-458-ProjectNonLinearSystems/build/project_ folder (the semicolon separator must be desactived, but the coma separator must be actived).<br/> 
You will see differents exemples of equations our project can solve, and parameters you can input. Now launch the main with no argument : it will take the **data.csv** file in input by default :
	
	./run

Look the answer on the terminal :<br/>
* First the warnings : They enhance missing or incoherent element in the csv. <br/>
* Next, the solutions find by numerical methods.

	
## Test your function : how to fill the csv
### first column : Choose your method 
* empty -> All the method
* n for newton;
* b for Bisection;
* c for Classic Chord;
* f for Fixed Point method
> n;b;c  # newton, Chord and Bisection will be computed
### 2nd column : The equation 
 #### First option: mathematic expression:
 Write the function in the column.
 Use
 * ```x``` as variable
 * ```^``` for power  
 * You can use external function 
   * ```exp(..)```
   * ```log(..)```
   * ```sqrt(..)```
   * ```cos(..)```
   * ```sin(..)```
   * ```tan(..)```
   * ```atan(..)```

 #### 2nd option: with c++ code on an external file:
 Put the name of the function as it appears in the cpp file. You should also fill the 9th column by adding the Name of the cpp file.<br/>
 The cpp file has to be in the same folder than the CSV File. Be carreful those functions have to be inclueded in a _extern "C"_ 
 
 	extern "C" {
		double nameFuncion(double x){return 2*x;}
	}
The simpliest way is to use the **function.cpp** file at disposition in _/build/project/_ and copy/paste the functions you want to test. 

### 3th column : The derivative 
If you want to use the Newton method, you need to fill the derivative of the equation. You can choose between the two way explained just before. 
Note that for the 2nd way, the function and its derivative have to be in the same cpp file.
You can let this column empty if you don't want to use de Newton method. <br/>
### 4th and 5th column : Bounds   
It's the lower and upper bound for the Bisection. You can let them empty if you don't want to use this method.
### 6th column : Initial Value
The initial value for Chord, Newton and fixed point. You can let it empty if you don't want to use these methods.
### 7th column : tolerance
The exactness you want to reach with the method. If you let it empty, the tolerance will be set by default at 0.000001.
### 8th column : Max iteration
The maximum number of iteration you will allow before stoping the method. If you let it empty, the maximum iterations will be set by default at 10000.
### 9th column : External file name
Only when we use a external cpp for the function.

## Your turn to test 
You can now use this csv file to put your own function. If you want to use your own csv, launch the main (  	```
	./run
	``` 
)with the csvfile path as argument. The simpliest way is to clear our exemples in the data.csv and use it for your test (_run_ will use this file by default if it has any argument).
Note that _run_ will always read all lines of the CSV and solves them.

## A note on the other main and non linear system
The other excutable file _runSystem_ is our extension of the project : Solving system with newton Method. <br/>
This branch is actually in working and we only have implement the solver with a quick exemple. 
We have the strategy to represent system and its jacobien matrice but we only lack an interface (like the csv file) to run different exemple without remake the project.<br/>
You can therefore run:
  	```
	./runSystem
	```
and it will solve the system :<br/>
f1 = x0^2+x0*x1-10<br/>
f2 = x1+3*x0*x1^2-57

# Implementation
The resolution of the equation is done with two main steps, the reading phase and the solving phase.
#### Generate documentation
Come back in the root floder git MATH-458-ProjectNonLinearSystems
To generate doxygen documentation:

	doxygen Doxyfile
If doesn't work you can create the Doxyfile with ```doxywizard``` and select the folder project to scan with scan recursively.<br>
To open the html web page:

	cd html
	firfox index.html


## Reader
Classes used to read the csv are in the [Project/ReadData](https://github.com/eseiler18/MATH-458-ProjectNonLinearSystems/tree/main/project/readData) folder, the main class is **ReaderData**. The role of this object is to read each row of the csv file to create **Data** structures (see [data.h](https://github.com/eseiler18/MATH-458-ProjectNonLinearSystems/tree/main/project/readData/Data.h)) which contain parameters of numerical methods input by the user.<br>
The interesting aspects of the implementation concern the reading of functions (the equation and its derivative column 2 and 3 of the csvfile). <br>
The **AbstractInterpreterFunction** is a common interface which contain a pure virtual method _createExecutableFunction_. There are two way inputting the desire functions, with its mathematical expression or with C++ code in an external file. Each of them has a class which inherits from **AbstractInterpreterFunction** and the _createExecutbaleFunction_ method return an **AbstractNode** object which is the executable function

### From mathematical expression
Classes used to interpret function from expression are in the folder [Project/ReadData/Parser](https://github.com/eseiler18/MATH-458-ProjectNonLinearSystems/tree/main/project/readData/parser).
The following diagram explains the process passing from an expression to an executable function for ```x+3x^2*5```.
![Parser](/figure/figParser.png "Parser")
First there is the reading phase done by the _readTokens_ method of the **Parser** class which attribute to each character a token. A token is the representation of a character or a group of character with a certain token type (see [TokenType.h](https://github.com/eseiler18/MATH-458-ProjectNonLinearSystems/tree/main/project/readData/parser/TokenType.h). There are created from an **AbstractToken** class. <br>
Then the _normalizeAndVerifyTokens_ method of the **Parser** class manages implicit operations, verifies validity of each token, and manages operation priorities by adding implicit parentheses.
![Builder](/figure/figBuilder.png "Builder")
Finally, there is the building phase of the executable function from tokens done by the _build_ method of the **Builder** class. The executable function is built as a binary tree with operator as node and number, variables, functions as leaf.<br> 
Nodes are created from the **AbstractNode** class which contains a pure virtual method _solve_. **OperatorNode**, **VariableNode**, **NumberNode**, and **FunctionNode** inherits from **AbstractNode**. Then we can access the value of the function for all x calling the _solve_ method on the root **AbstractNode** of the tree. It recursively calls _solve_ method of each node to compute the result (note that the tree is built only one time at reading step).  
### From c++ code
Accessing the function from c ++ code is much easier since the function is already built and can be interpreted by the program. To recover the function from an external cpp file we dynamically compile it with the _system_ command and create a library in the /tmp folder. The library is load and a function pointer is created from the name of the function in the cppfile. Then an **ExternalFunctionNode** which inherits of **AbstractNode** is created to fit with the common interface **AbstractInterpreterFunction** (a tree is built with just one vertex and value of the function can be access with the _solve_ method of **AbstractNode**).
## Solver
All classes concerning solving step can be found in the folder project/solverMethods.
After the reading step, informations about the equation and the numerical methods are stored in a structure **Data** (see [data.h](https://github.com/eseiler18/MATH-458-ProjectNonLinearSystems/tree/main/project/readData/Data.h)).
The equation is solved from an **AbstractSolveur** class which contains common element of all numerical methods (equation, tolerance, number of maximum iterations) and a pure virtual method call _SolveEquation_.<br>
Then the four methods implemented have an associated class which inherits from **AbstractSolver**.  With polymorizm _SolveEquation_ method returns the result of the equation or an exception if the method doesn't converge.<br>
A little word on the **NewtonSystem** class which is implemented to solve system with several variable (does not inherit from **AbstractSolveur**). The eigen library is used to create a vector and a matrix of **AbstractNode** which corresponds to equations and the Jacobian of the system.
# Validating Test
## What we Testing
All the tests are in the test.cc file you can find on [google_test folder](https://github.com/eseiler18/MATH-458-ProjectNonLinearSystems/tree/main/google_test)
Two fixtures are implemented, _SetUp_ is implemented in each one to facilitate the Test.
### Testing the Parseur
This corresponds to the fixture **Fixture_Interpreter**. The goal is to check all the corner cases of the parser and verify if it can reconstruct the desired fonction.
We compare the constructed function with the real one, and assert if our parser can actually :<br/>
- can make simple operation ```+``` ```-``` ```*``` and ```/```
- respect priorities of operation
- respect the ```(..)``` priority
- recognise the function we have implemented like cos, exp etc ...
- handle with the multi-variables functions ( ```x0```, ```x1``` etc ...)

We also assert that the parser throws the desired error when it detects a incoherence :
- begin with a operator``` + ```, ``` * ``` or ```/```
- operator follow by another operator : ``` ( 5 + * 4) ``` , same with number ``` ( 2 3 +4) ```
- non recognise function : ``` skz(x) ```
- a parenthesis not open or not close : ``` 3*4x ) ```

### Testing the Method
This corresponds to the fixture **Fixture_Solve**.<br/>
We actually test if numerical methods work correctly. The _SetUp_ takes in argument features of a function and returns the output.
* Test working cases for the four different methods
* Assert that the method throws an exception when it diverges to infinity ( > #throw **ExceptionIterate** ).
* Assert that the method trows an exception when it converges to a wrong solution ( > ```x^2 +1```   #throw **ExceptionIterate**).
* Assert that some corner case throws the desired error (> For Bisection if f(a) * f(b) >0 , #trow **std::invalid_argument** ).

# Limitation and perspective
## More way to input functions:
For now our project allows the user to input functions with a mathematical expression or a c++ code. But we have good reasons to think that the user wants to input other type, for example tabular functions. Then to implement, we just must create a class **InterpreterTablular** which inherits of **AbstractInterpreterFunction** with the file in parameter. Then the _createExecutableFunction_ method of this class must analyse the content of the file and return an **AbstractNode** which is the executable function. 

## Finish System Implementation:
The extension to system solver isn’t finished yet. As you can see in the runSystem.cpp file the solving part is implemented and works with mathematical expression. But the reading part isn’t implemented yet, the user can’t give his own system (if you want to test you can change the example in runSystem.cpp but you need to recompile). However, the parser works with several variables (x0, x1, x2…) and the _solve_ method of **AbstractNode** is polymorphized with several variables to access value of multi variables functions.
