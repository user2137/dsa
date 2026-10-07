//SLIP - 25
//Q.1
#include<stdio.h>

#define MAX 10
#define INF 999

int main(){
    int n,i,j,min,u;
    int cost[MAX][MAX],dist[MAX],visited[MAX]={0};

    printf("Enter number of vertices: ");
    scanf("%d",&n);

    printf("Enter cost matrix:\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d",&cost[i][j]);
        }
    }

    int source;
    printf("Enter source vertex: ");
    scanf("%d",&source);

    for(i=0;i<n;i++){
        dist[i]=cost[source][i];
    }
    visited[source]=1;

    for(i=1;i<n;i++){
        min=INF;

        for(j=0;j<n;j++){
            if(!visited[j] && dist[j]<min){
                min=dist[j];
                u=j;
            }
        }

        visited[u]=1;

        for(j=0;j<n;j++){
            if(!visited[j] && (dist[u]+cost[u][j]<dist[j])){
                dist[j]=dist[u]+cost[u][j];
            }
        }
    }

    printf("\nShortest distances:\n");
    for(i=0;i<n;i++){
        printf("%d -> %d = %d\n",source,i,dist[i]);
    }

    return 0;
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 

CREATE TABLE Customer (
 cno INT PRIMARY KEY,
 cname VARCHAR(20),
 city VARCHAR(20)
);

CREATE TABLE Account (
 a_no INT PRIMARY KEY,
 a_type VARCHAR(10),
 opening_date DATE,
 balance MONEY,
 cno INT REFERENCES Customer(cno)
);

//INSERT VALUES 

INSERT INTO Customer VALUES
(1,'Om','Pune'),
(2,'Amit','Mumbai'),
(3,'Ravi','Pune');

INSERT INTO Account VALUES
(101,'Saving','2024-01-01',5000,1),
(102,'Current','2024-02-01',8000,2),
(103,'Saving','2024-03-01',6000,3);

//TRIGGER

CREATE OR REPLACE FUNCTION prevent_delete()
RETURNS trigger AS $$
BEGIN
 IF OLD.a_type = 'Saving' THEN
  RAISE EXCEPTION 'Cannot delete Saving Account';
 END IF;

 RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_delete
BEFORE DELETE ON Account
FOR EACH ROW
EXECUTE FUNCTION prevent_delete();

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE pune_customers()
AS $$
DECLARE
 rec RECORD;
BEGIN
 FOR rec IN SELECT * FROM Customer WHERE city='Pune'
 LOOP
  RAISE NOTICE 'Cno: %, Name: %, City: %',
  rec.cno, rec.cname, rec.city;
 END LOOP;
END;
$$ LANGUAGE plpgsql;