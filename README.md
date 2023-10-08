# Network_science_final_project

## Project:
Ego-splitting Framework in C++

## Project Type:
Implementation-flavor 

## Paper Link:
https://dl.acm.org/doi/10.1145/3097983.3098054 

## Code Implementation :
C++ 

## Group: 9

## Contrubutors:
Raj Indroju, Sai Krishna Reddy Kandhadi, Pratyush Reddy Gaggenapalli

## Github URL: 
https://github.com/PratyushGR/Network_science_final_project.git

# Input DataSets: 

Data sets are provided int the Inputs directory we have tested our source code on 4 different datasets
<img width="641" alt="image" src="https://user-images.githubusercontent.com/99221826/205421753-4be3ed68-9fc0-49fb-aa87-d25cf8d5b277.png">

## a. Test
This is small graph authors have used to explain the framework in the research paper.  Graph with 9 nodes and 11 edges. 
<img width="236" alt="image" src="https://user-images.githubusercontent.com/99221826/205421936-d49ae0aa-cccc-4354-b06a-4e2fb6494c59.png">
			
	
## b. Tv_show edges
Data collected about Facebook pages (November 2017). These datasets represent blue verified Facebook page networks of different categories. Nodes represent the pages and edges are mutual likes among them.
<img width="512" alt="image" src="https://user-images.githubusercontent.com/99221826/205421909-281df20d-187b-45a0-8243-42f26b399a58.png">


## c. DBLP
The DBLP computer science bibliography provides a comprehensive list of research papers in computer science. We construct a co-authorship network where two authors are connected if they publish at least one paper together. Publication venue, e.g, journal or conference, defines an individual ground-truth community; authors who published to a certain journal or conference form a community. We regard each connected component in a group as a separate ground-truth community. We remove the ground-truth communities which have less than 3 nodes. We also provide the top 5,000 communities with highest quality which are described in our paper. As for the network, we provide the largest connected component.

<img width="317" alt="image" src="https://user-images.githubusercontent.com/99221826/205421895-9eac5ffd-d944-4c2a-afec-a35714531537.png">

## tester_edges
This is small graph authors have used to explain the framework in the research paper.  Graph with 10 nodes and 28 edges. 

![image](https://user-images.githubusercontent.com/99221826/205423811-ed1d00d6-481e-4679-86a0-5e7a8d2c0074.png)


# Code Execution
we have implemented our project in C++ from scratch and we have not used any complex libraries any cpp compiler with right configuration would be able to run our script.

# please follow the below steps before executing the script
##### Step1:
verify your G++ version, download it from https://formulae.brew.sh/formula/gcc or for Vs-code https://code.visualstudio.com/docs/languages/cpp

<img width="442" alt="image" src="https://user-images.githubusercontent.com/99221826/205422337-597e29f7-1fdf-47af-b85e-b30bff5094ad.png">

##### step2:
Set correct Input file path to "file_name" variable in the main function in ego_split.cpp file in order to execute our algorithm on the provided data set and plot get the desired splitted ego's for each node

<img width="398" alt="image" src="https://user-images.githubusercontent.com/99221826/205422118-fb213d42-4415-4456-87e8-c6ebd7ab9d8d.png">

##### step3:
Execute the script and save the output to log file as below command

g++ /path/to/file/ego_split.cpp -o /path/to/file/ego_split && /path/to/file/ego_split >> /path/to/log_file/tester_edges.log

# Here is a sample output file which will be generated on successful execution of our algorithm
<img width="494" alt="image" src="https://user-images.githubusercontent.com/99221826/205422713-4be70859-8793-4cc4-bfc3-642b8cc8ec44.png"><img width="494" alt="image" src="https://user-images.githubusercontent.com/99221826/205422725-2af69e61-8847-4575-b5c5-00cf722637ce.png">

<img width="814" alt="image" src="https://user-images.githubusercontent.com/99221826/205422779-97386d01-a1f8-49d7-b3e8-b12fe3876991.png">

We have uploaded our exectionlogs on the above 4 data sets in the outputs folder

<img width="717" alt="image" src="https://user-images.githubusercontent.com/99221826/205423939-bc24ce82-632d-44b9-99be-acb278e49ad9.png">


# Evaluation of our ego-splitting algorithm

We have uploade a Evalauation.ipynd file in our project.
Our evaluation foloows the follow steps,

#### Step 1:
As our source code is completly developed in C++ we have created some modules in python and pasted our final Overlapping Partitions outupt from logfile to our Ipynb file and the generated communities from it.

<img width="1093" alt="image" src="https://user-images.githubusercontent.com/99221826/205423100-8b53af2e-5134-482e-9143-11a3fcfc19a1.png">

#### Step 2:

Then we have generated communities for our Overlapping partitions generated from each dataset using the below function
<img width="1093" alt="image" src="https://user-images.githubusercontent.com/99221826/205423151-cff63940-e327-42ea-bf7c-02851d39cb7a.png">

Here is a sample output for the communities generated for Tester_edges data set

<img width="418" alt="image" src="https://user-images.githubusercontent.com/99221826/205423217-914139df-0668-427f-98fb-24a07a2fd041.png">

#### Step 3: For caliculating F1 scores we have used the following algorithms proved in nf1 and cdlib packages of python

<img width="668" alt="image" src="https://user-images.githubusercontent.com/99221826/205423526-dc93ef64-fd89-437a-91a7-57a25a3fb34e.png">

<img width="816" alt="image" src="https://user-images.githubusercontent.com/99221826/205423376-a54da47d-4215-44b5-b5cc-a99279caa4bf.png">

















