//SLIP - 4
//Q.1

#include <stdio.h>

int visited[10];

void dfs(int a[10][10], int n, int v){
    printf("%d ",v);
    visited[v]=1;

    for(int i=0;i<n;i++){
        if(a[v][i]==1 && visited[i]==0)
            dfs(a,n,i);
    }
}

int main(){
    int n,a[10][10];

    scanf("%d",&n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d",&a[i][j]);

    dfs(a,n,0);
    return 0;
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 
CREATE TABLE Movies (
 m_name VARCHAR(25) PRIMARY KEY,
 release_year INT,
 budget MONEY
);

CREATE TABLE Actor (
 a_name CHAR(30),
 role CHAR(30),
 charges MONEY,
 a_address VARCHAR(30),
 PRIMARY KEY(a_name, role)
);

CREATE TABLE Producer (
 producer_id INT PRIMARY KEY,
 name CHAR(30),
 p_address VARCHAR(30)
);

-- Actor-Movie (M-M)
CREATE TABLE Movie_Actor (
 m_name VARCHAR(25) REFERENCES Movies(m_name),
 a_name CHAR(30),
 role CHAR(30),
 PRIMARY KEY(m_name, a_name, role)
);

-- Producer-Movie (M-M)
CREATE TABLE Movie_Producer (
 m_name VARCHAR(25) REFERENCES Movies(m_name),
 producer_id INT REFERENCES Producer(producer_id),
 PRIMARY KEY(m_name, producer_id)
);

//INSERT VALUES 
INSERT INTO Movies VALUES
('Movie1',2023,6000000),
('Movie2',2022,8000000);

INSERT INTO Actor VALUES
('Amit','Hero',500000,'Mumbai'),
('Ravi','Villain',300000,'Pune');

INSERT INTO Producer VALUES
(1,'Karan','Mumbai'),
(2,'Rohit','Pune');

INSERT INTO Movie_Actor VALUES
('Movie1','Amit','Hero'),
('Movie2','Ravi','Villain');

INSERT INTO Movie_Producer VALUES
('Movie1',1),
('Movie2',2);

//TRIGGER
CREATE OR REPLACE FUNCTION check_budget()
RETURNS trigger AS $$
BEGIN
 IF NEW.budget < 5000000 THEN
  RAISE EXCEPTION 'Budget should be minimum 50 lakh';
 END IF;

 RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_movie
BEFORE INSERT ON Movies
FOR EACH ROW
EXECUTE FUNCTION check_budget();


//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE check_number(n INT)
AS $$
BEGIN
 IF n > 0 THEN
  RAISE NOTICE 'Positive Number';
 ELSIF n < 0 THEN
  RAISE NOTICE 'Negative Number';
 ELSE
  RAISE NOTICE 'Zero';
 END IF;
END;
$$ LANGUAGE plpgsql;
