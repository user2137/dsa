//SLIP - 8
//Q.1

#include <stdio.h>

void heapify(int a[],int n,int i){
    int largest=i,l=2*i+1,r=2*i+2;

    if(l<n && a[l]>a[largest]) largest=l;
    if(r<n && a[r]>a[largest]) largest=r;

    if(largest!=i){
        int t=a[i]; a[i]=a[largest]; a[largest]=t;
        heapify(a,n,largest);
    }
}

void heapsort(int a[],int n){
    for(int i=n/2-1;i>=0;i--)
        heapify(a,n,i);

    for(int i=n-1;i>=0;i--){
        int t=a[0]; a[0]=a[i]; a[i]=t;
        heapify(a,i,0);
    }
}

int main(){
    int n,a[20];
    scanf("%d",&n);

    for(int i=0;i<n;i++) scanf("%d",&a[i]);

    heapsort(a,n);

    for(int i=0;i<n;i++) printf("%d ",a[i]);

    return 0;
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 
CREATE TABLE TRAIN (
 train_no INT PRIMARY KEY,
 train_name VARCHAR(20),
 depart_time TIME,
 arrival_time TIME,
 source_stn VARCHAR(20),
 dest_stn VARCHAR(20),
 no_of_res_bogies INT,
 bogie_capacity INT
);

CREATE TABLE PASSENGER (
 passenger_id INT PRIMARY KEY,
 passenger_name VARCHAR(20),
 address VARCHAR(30),
 age INT,
 gender CHAR
);
-- M-M RELATION (TICKET)
CREATE TABLE TICKET (
 train_no INT REFERENCES TRAIN(train_no),
 passenger_id INT REFERENCES PASSENGER(passenger_id),
 ticket_no INT,
 bogie_no INT,
 no_of_berths INT,
 tdate DATE,
 ticket_amt DECIMAL(7,2),
 status CHAR CHECK (status IN ('W','C')),
 PRIMARY KEY(train_no, passenger_id, ticket_no)
);

//INSERT VALUES 
INSERT INTO TRAIN VALUES
(1,'Express','10:00','14:00','Pune','Mumbai',5,72),
(2,'Superfast','12:00','18:00','Mumbai','Nashik',6,80);

INSERT INTO PASSENGER VALUES
(101,'Om','Pune',10,'M'),
(102,'Amit','Mumbai',4,'M');

INSERT INTO TICKET VALUES
(1,101,1001,1,2,'2024-01-01',500.00,'C'),
(2,102,1002,2,1,'2024-01-02',300.00,'W');

//TRIGGER
CREATE OR REPLACE FUNCTION age_check()
RETURNS trigger AS $$
BEGIN
 IF NEW.age > 5 THEN
  RAISE NOTICE 'Age above 5 will be charged full fare';
 END IF;

 RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_passenger
AFTER INSERT ON PASSENGER
FOR EACH ROW
EXECUTE FUNCTION age_check();

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE calc(a INT, b INT)
AS $$
BEGIN
 RAISE NOTICE 'Addition: %', a + b;
 RAISE NOTICE 'Subtraction: %', a - b;
 RAISE NOTICE 'Multiplication: %', a * b;
END;
$$ LANGUAGE plpgsql;
