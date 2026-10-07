//SLIP - 30
//Q.1
#include<stdio.h>

#define MAX 10

int parent[MAX];

int find(int i){
    while(parent[i])
        i = parent[i];
    return i;
}

int union_set(int i, int j){
    if(i != j){
        parent[j] = i;
        return 1;
    }
    return 0;
}

int main(){
    int n = 4;
    int cost[10][10] = {
        {0,2,999,6},
        {2,0,3,8},
        {999,3,0,0},
        {6,8,0,0}
    };

    int min, a, b, u, v;
    int ne = 1, mincost = 0;

    while(ne < n){
        min = 999;

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(cost[i][j] < min){
                    min = cost[i][j];
                    a = u = i;
                    b = v = j;
                }
            }
        }

        u = find(u);
        v = find(v);

        if(union_set(u,v)){
            printf("Edge %d: (%d-%d) cost=%d\n", ne++, a, b, min);
            mincost += min;
        }

        cost[a][b] = cost[b][a] = 999;
    }

    printf("Minimum Cost = %d\n", mincost);
    return 0;
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 

CREATE TABLE Student (
 Roll_No INT PRIMARY KEY,
 Sname VARCHAR(20),
 Sclass CHAR(10)
);

CREATE TABLE Teacher (
 T_No INT PRIMARY KEY,
 Tname CHAR(20),
 Experience INT
);

CREATE TABLE Student_Teacher (
 Roll_No INT REFERENCES Student(Roll_No),
 T_No INT REFERENCES Teacher(T_No),
 Subject VARCHAR(20),
 PRIMARY KEY(Roll_No, T_No)
);

//INSERT VALUES 

INSERT INTO Student VALUES
(1,'Om','SY'),
(2,'Amit','SY');

INSERT INTO Teacher VALUES
(101,'Sharma',12),
(102,'Patil',8);

INSERT INTO Student_Teacher VALUES
(1,101,'DBMS'),
(2,102,'DS');

//TRIGGER

CREATE OR REPLACE FUNCTION check_roll()
RETURNS trigger AS $$
BEGIN
 IF NEW.Roll_No <= 0 THEN
  RAISE EXCEPTION 'Invalid Roll Number';
 END IF;

 RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_roll
BEFORE INSERT ON Student
FOR EACH ROW
EXECUTE FUNCTION check_roll();

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE sum_avg(n INT)
AS $$
DECLARE 
 i INT := 1;
 s INT := 0;
 avg_val NUMERIC;
BEGIN
 WHILE i <= n LOOP
  s := s + i;
  i := i + 1;
 END LOOP;

 avg_val := s::NUMERIC / n;

 RAISE NOTICE 'Sum = %', s;
 RAISE NOTICE 'Average = %', avg_val;
END;
$$ LANGUAGE plpgsql;