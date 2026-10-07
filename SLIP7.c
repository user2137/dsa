//SLIP - 7
//Q.1

#include <stdio.h>
#define INF 999

int main(){
    int n,cost[10][10],dist[10],visited[10]={0};

    scanf("%d",&n);

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d",&cost[i][j]);

    int src=0;

    for(int i=0;i<n;i++){
        dist[i]=cost[src][i];
    }

    visited[src]=1;

    for(int i=0;i<n-1;i++){
        int min=INF,u;
        for(int j=0;j<n;j++){
            if(!visited[j] && dist[j]<min){
                min=dist[j];
                u=j;
            }
        }

        visited[u]=1;

        for(int v=0;v<n;v++){
            if(!visited[v] && dist[v] > dist[u]+cost[u][v])
                dist[v]=dist[u]+cost[u][v];
        }
    }

    for(int i=0;i<n;i++)
        printf("%d ",dist[i]);

    return 0;
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 
CREATE TABLE Branch (
 br_id INT PRIMARY KEY,
 br_name CHAR(30),
 br_city CHAR(10)
);

CREATE TABLE Customer (
 cno INT PRIMARY KEY,
 c_name CHAR(20),
 caddr CHAR(35),
 city CHAR(20)
);

CREATE TABLE Loan_application (
 lno INT PRIMARY KEY,
 l_amt_required MONEY CHECK (l_amt_required > 0),
 l_amt_approved MONEY,
 l_date DATE
);

-- TERNARY RELATION
CREATE TABLE Ternary (
 br_id INT REFERENCES Branch(br_id),
 cno INT REFERENCES Customer(cno),
 lno INT REFERENCES Loan_application(lno),
 PRIMARY KEY(br_id, cno, lno)
);

//INSERT VALUES 
INSERT INTO Branch VALUES
(1,'SBI','Pune'),
(2,'HDFC','Mumbai');

INSERT INTO Customer VALUES
(101,'Om','Pune Addr','Pune'),
(102,'Amit','Mumbai Addr','Mumbai');

INSERT INTO Loan_application VALUES
(201,50000,40000,'2024-01-01'),
(202,70000,60000,'2024-02-01');

INSERT INTO Ternary VALUES
(1,101,201),
(2,102,202);

//TRIGGER
CREATE OR REPLACE FUNCTION check_customer()
RETURNS trigger AS $$
BEGIN
 IF NEW.cno <= 0 THEN
  RAISE EXCEPTION 'Invalid Customer Number';
 END IF;

 RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_customer
BEFORE INSERT ON Customer
FOR EACH ROW
EXECUTE FUNCTION check_customer();

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE sum_n(n INT)
AS $$
DECLARE
 i INT := 1;
 s INT := 0;
BEGIN
 WHILE i <= n LOOP
  s := s + i;
  i := i + 1;
 END LOOP;

 RAISE NOTICE 'Sum = %', s;
END;
$$ LANGUAGE plpgsql;
