//SLIP - 27
//Q.1
#include<stdio.h>
#define INF 999

int main(){
    int n=4,cost[10][10]={
        {0,2,INF,6},
        {2,0,3,8},
        {INF,3,0,0},
        {6,8,0,0}
    };

    int visited[10]={0},min,a,b;

    visited[0]=1;

    for(int k=0;k<n-1;k++){
        min=INF;

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(cost[i][j]<min && visited[i] && !visited[j]){
                    min=cost[i][j];
                    a=i; b=j;
                }
            }
        }

        printf("Edge: %d - %d\n",a,b);
        visited[b]=1;
    }
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 

CREATE TABLE Student (
 rollno INT PRIMARY KEY,
 name VARCHAR(30),
 class VARCHAR(10)
);

CREATE TABLE Subject (
 scode VARCHAR(10) PRIMARY KEY,
 subject_name VARCHAR(20)
);

CREATE TABLE Student_Subject (
 rollno INT REFERENCES Student(rollno),
 scode VARCHAR(10) REFERENCES Subject(scode),
 marks_scored INT,
 PRIMARY KEY(rollno, scode)
);

//INSERT VALUES 

INSERT INTO Student VALUES
(1,'Om','SY'),
(2,'Amit','SY'),
(3,'Ravi','FY');

INSERT INTO Subject VALUES
('S1','Math'),
('S2','DBMS');

INSERT INTO Student_Subject VALUES
(1,'S1',80),
(1,'S2',70),
(2,'S1',60),
(3,'S2',50);

//TRIGGER

CREATE OR REPLACE FUNCTION check_marks()
RETURNS trigger AS $$
BEGIN
 IF NEW.marks_scored < 0 THEN
  RAISE EXCEPTION 'Marks cannot be negative';
 END IF;

 RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_marks
BEFORE INSERT OR UPDATE ON Student_Subject
FOR EACH ROW
EXECUTE FUNCTION check_marks();

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE calc(a INT, b INT)
AS $$
BEGIN
 RAISE NOTICE 'Addition: %', a+b;
 RAISE NOTICE 'Subtraction: %', a-b;

 IF b = 0 THEN
  RAISE EXCEPTION 'Division by zero not allowed';
 ELSE
  RAISE NOTICE 'Division: %', a/b;
 END IF;
END;
$$ LANGUAGE plpgsql;