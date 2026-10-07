//SLIP - 21
//Q.1
#include <stdio.h>
#define MAX 10

int adj[MAX][MAX], indegree[MAX], n;

void topo(){
    int i,j,k;

    for(i=0;i<n;i++) indegree[i]=0;

    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(adj[i][j]==1)
                indegree[j]++;

    printf("Topological Order: ");
    for(k=0;k<n;k++){
        for(i=0;i<n;i++){
            if(indegree[i]==0){
                printf("%d ",i);
                indegree[i]=-1;

                for(j=0;j<n;j++)
                    if(adj[i][j]==1)
                        indegree[j]--;
                break;
            }
        }
    }
}

int main(){
    int i,j;

    printf("Enter vertices: ");
    scanf("%d",&n);

    printf("Enter adjacency matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&adj[i][j]);

    topo();
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 
CREATE TABLE Hospital (
 h_no INT PRIMARY KEY,
 h_name VARCHAR(20),
 city VARCHAR(10)
);

CREATE TABLE Doctor (
 d_no INT PRIMARY KEY,
 d_name VARCHAR(30),
 specialization VARCHAR(35),
 phone_no INT,
 charges INT,
 h_no INT REFERENCES Hospital(h_no)
);

//INSERT VALUES 

INSERT INTO Hospital VALUES
(1,'CityCare','Pune'),
(2,'LifeLine','Mumbai');

INSERT INTO Doctor VALUES
(101,'Dr.Amit','Cardio',12345,500,1),
(102,'Dr.Ravi','Neuro',67890,700,1),
(103,'Dr.Sneha','Ortho',11111,600,2);

//TRIGGER
CREATE OR REPLACE FUNCTION check_charges()
RETURNS trigger AS $$
BEGIN
 IF NEW.charges < 0 THEN
  RAISE EXCEPTION 'Charges cannot be negative';
 END IF;

 RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_doctor
BEFORE INSERT OR UPDATE ON Doctor
FOR EACH ROW
EXECUTE FUNCTION check_charges();

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE insert_doctor(
 dno INT,
 dname VARCHAR,
 spec VARCHAR,
 phone INT,
 charge INT,
 hno INT
)
AS $$
BEGIN
 INSERT INTO Doctor VALUES(dno, dname, spec, phone, charge, hno);
 RAISE NOTICE 'Doctor inserted successfully';
END;
$$ LANGUAGE plpgsql;
