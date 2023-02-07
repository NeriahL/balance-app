# balance-app

Welcome to Balance App!

This is an app for managing customer debt.

The program starts by printing a list of the customers and their current balance.

There are four legitimate commands:

1. set. - This command adds a new entry to the database and alters the customer list and their balances accordingly.
  Proper format => set first name=<name> , last name=<name> , id=<id> , phone number=<phone number> , date=<date<month/day/year>> , debt=<debt>

2. select. - This command searches the list, by any parameter. Note, it searches the list of customers in the program, not the list of entries in the database.
  Proper format => select <parameter<first name/last name...>><operator<'='/'<'/'>'/'!='><value<name/date/debt...>

3. print. - This command prints the list of customers and their current balance.

4. quit. - This command quits the program.

5. send. - This command sends queries to server.


In order to compile and run this program there are several options:
  
  1. To run locally, compile with 'make local' and run with ./local.

  2. To run in client-sever mode, compile the server with 'make remote' and the client side with 'gcc client.c -o client'.
     To run sever type './remote <port> <database>' and to run client, type './client <port>'.
  
  ```mermaid
graph TD;
  Query-->Set-->Send to Server-->Fill_Attributes-->Save to List-->Write to database
  Query-->Select-->Send to Server-->Select from List-->Send to Client
  Query-->Print-->Send to Server-->Get List-->Send to Client
  Query-->Send-->Send to Server
  Query-->Quit-->Leave Program
  Query-->'Enter'-->Send to Server
```
