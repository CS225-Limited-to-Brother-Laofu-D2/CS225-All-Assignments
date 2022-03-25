Programming Assignment 1
Due Date: April 8, 2021, 23:59
The task of this programming assignment is to implement a registration, queueing and reporting system for mass medical treatment (such as vaccination). The system is to support
the following operations:
Registration. A person can register for medical treatment at a local registry. For the registration the following information is required:
– the identification number of the person,
– the name and contact details (address, phone, WeChat, email) of the person,
– the profession of the person,
– the date of birth of the person,
– the medical risk status of the person.
Each registration record will receive a timestamp, i.e. the date and the time of the registration will be stored.
The professions are classified into eight profession categories I to VIII. There are seven
age groups: children (≤ 12 years), adolescents (≤ 18 years), young adults (≤ 35 years),
adults (≤ 50 years), seniors (≤ 65 years), elderly people (≤ 75 years), and old people
(> 75 years). There are four different risk status: no risk (0), low risk (1), medium risk
(2), and high risk (3).
Registration records are stored permanently. In addition, records with relevant information such as identification, profession category, age category, risk status, registration date
and time are kept in a queue, which twice daily is forwarded to the centralised treatment
queue. Data from different local registries is added to the centralised queue in random
order, but the order from the local queues is preserved.
Queueing and assignment of appointments. The assignment of an appointment for receiving treatment is organised according to priority. The most important criterion is the
profession category followed by a ranking of age groups, and further followed by data and
time of the registration. Only people with no or low risk are considered. For people with
medium risk a one month extension is added; people with high risk are only considered
when there are no others waiting in the queue.
A person may withdraw from the treatment at any time. Those who have withdrawn and
then registered again are considered with additional two weeks waiting time, unless they
are in the medium or high risk group.
Furthermore, the profession category and the risk status of a queueing person may change.
If this affects increases the priority in the queue, the relevant attributes are updated. A
person may also present a priority letter with a deadline for the treatment. At the latest
a person is assigned an appointment before the deadline regardless of the other selection
criteria.
Appointment processing. When a person has highest priority in the priority queue, an
appointment location, date and time (usually the next day) is assigned and registered.
With this the person leaves the queue. There are several locations for treatment processing
CS 225 – Data Structures ZJU-UIUC / Klaus-Dieter Schewe Spring 2022 / 1
each with a daily capacity and associated time slots for the treatment. Usually, the closest
location is selected for a person.
The right to withdraw is reserved. When the treatment has been processed at the designated location at the reserved day and time, this is also registered.
Reporting. The system shall produce weekly reports comprising
– the people who have been treated including their profession category, age category,
risk status and the waiting time from registration to treatment,
– the registered people with a set appointment including their profession category, age
category, risk status and their waiting time until now,
– the queueing people without a set appointment including their profession category,
age category, risk status and their waiting time until now.
It must be possible to order these reporting lists by name, profession category or age
group.
In addition the system shall produce a monthly statistics report showing how many people
have registered, how many of them are waiting, how many are waiting in total, how many
treatment appointments have been made, the average waiting time, and the number of
people who withdrew their registration.
Programming Tasks
Use C++ unless the use of a different programming language has been endorsed by the course
instructor.
(i) For the registration records use files for each local registry.
(ii) Implement data structures for the local queues.
(iii) Implement a Fibonacci heap for the centralised treatment queue.
(iv) Implement lists for the appointments at each location.
(v) Implement the update, selection and reporting functions described above.
total points: 100
CS 225 – Data Structures ZJU-UIUC / Klaus-Dieter Schewe Spring 2022 / 2
