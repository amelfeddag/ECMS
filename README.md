this is a mini project within our DSA course at ENSIA, it was prepared by proffessor Ahmed Guessoum and realized by me and my team : mustapha belkebir, ines benchrif, mouchaal ahmed el amine,

here are the instructions recieved in order to achieve this project: "enjoy"


The National Higher School of Artificial Intelligence
Data Structures and Algorithms 2

Programming Mini Project:
Electricity Network Management System

Submission deadline: Saturday 16/12/2023, not later than 11:59pm

The national electricity company wants to develop a system to manage the power consumption and 
billing by its customers on its national network. The company has organised the networks into regions 
and, within each region, into cities, and then districts within each city. The novelty is that the company 
has introduced the possibility that an individual customer can produce photovoltaic electricity and 
inject it into the network. So each customer could consume electricity from the network and/or inject 
electricity into it. Whether consumed or produced (i.e. injected into the network), the monthly amount
of electricity is indicated in Kilowatt hours in the bill the customer receives. Obviously, both 
quantities will vary depending on the season and the consumption or production. For instance, on 
sunny days the customer’s installations will be able to produce electricity and, any above the 
customer’s domestic needs will be injected into the network. If no electricity or not enough is 
produced, the customer’s house will consume electricity from the network. As such, the bill a 
customer gets at the end of the month will show the amount of electricity consumed during the month 
for which the company charges the customer 5 DA per kilowatt hour consumed, and the total amount 
of energy the customer has injected into the network for which he/she gets a credit of 3 DA per 
kilowatt hour injected. Depending on the difference between these two amounts, either the customer 
will pay the difference or gets money transferred to his bank account by the electricity company.



Because the company would like to eventually do a lot of mining of the data to better understand its 
customers and optimise the energy consumption, hence investments on new infrastructures, it keeps 
data about each household (customer). This data includes the name and ID number of the electricity 
account holder, the number of family members, and their ages. The company obviously has the 
address of the customer, hence his/her district, city, and region.


On the other hand, the company has for each city a marketing department with its specific budget. The 
role of this department is twofold: (1) encourage customers to produce energy that can be injected into 
the system (which will on the long run relieve the company from having to make more infrastructure 
investments which happen to be very costly); and (2) think of ways of getting customers to consume 
more electricity to maximise the company’s profit. Initially, each department at the national level gets 
a budget of 10 million dinars per year for their activities. (This does not include the department 
employees’ salaries, etc.). At the end of each year, the departments at the national level are sorted 
based on the total amounts paid by the customers, from the best performing department to the least. 
The best department will get an increase of 15% to its budget while the next 9 best performing 
departments will get an increase of 10% to their respective budgets. Inversely, the least performing 
department will get a decrease of 15% to its budget while the previous 9 least performing departments 
will get a decrease of 10% to their respective budgets. (The salaries of the employees will also 
logically be increased or decreased to reflect the performances of their respective departments, but you 
do not have to worry about this aspect in this mini-project.)



Since the company wants to encourage households to inject electricity into the network, a national 
prize is given monthly to the person who has injected the most energy. This amount is cumulative 
month after month. This means that a person who gets the prize one month would be a little 
advantaged the following month, though another customer could become the new national prize 
winner.


The Electricity Company Management System (ECMS) we want to build needs to keep all the needed 
data about the following:



 the information about each household as explained above;
 data about the electricity consumption and/or production by each household (i.e. customer);
 on each day of the year, whether the day is rainy/sunny/cloudy/snowy, the day maximum and 
minimum temperatures, and the number of sunny hours; and 
 the amount each department has spent on any month from the budget that was allocated to it.



This data will be kept and accumulated as appropriate over the years.
The ECMS should organise all this data in such a way that all operations of access to the data and of 
processing it to return the below results should be done as quickly as possible. (Though you are only 
asked to simulate the ECMS with data about the Algerian market, the company has a contract with a 
large number of other African companies to deploy the ECMS for their markets. Any data mining 
models could thus be developed at different levels within a country or even at a global African level. 
But you only need to worry about the Algerian market, bearing in mind that the system should 
eventually store data about so many countries.)
The ECMS is supposed to be web-based or mobile-based, but this is really optional; you can only 
implement the strictly necessary functionalities. But nicer systems will be positively appreciated.
Based on EXACTLY1 THE AFOREMENTIONED DATA, the results expected from the ECMS are 
the following, in addition to any other results you may wish to include and explain in your report why 
they are good additions.
 A bill for any customer.
 A listing summarising all the bills of the customers of a specified district or city or region or 
even country.
 A listing which shows the performance of each department, sorted from the best performing to 
the least performing department.
 One may wish to display any of the previous results for a given month, year, or even period 
(from a start date to an end date).
 Appropriate relevant figures (curves, bar charts, etc.) could be displayed for the previous 
results


Part A of the Project: 
We have decided to store the data in a Binary Search Tree (plus any other ADTs as you see 
appropriate)
1. Give the graphical representation of the most suitable ADT for the ECMS. This global 
ADT could be a combination of ADTs, each of which would be useful for any 
purposes you will need to explain.
2. Give a complete specification of this ADT.
3. Implement all the operations, making use as much as possible of any ADTs and 
operations we have studied in class.
4. Write a program which computes the average time for displaying the various results
mentioned above



Part B of the Project: 
We have decided to store the data in an AVL Tree.
5. Implement all the operations, making use as much as possible of any ADTs and 
operations we have studied in class.
6. Write a program which computes the average time for displaying the various results
mentioned above. 
7. Compare the results obtained in questions 4 and 6, and give your conclusion.





