//SLIP - 29
//Q.1
#include<stdio.h>

void heapify(int arr[], int n, int i){
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < n && arr[left] > arr[largest])
        largest = left;

    if(right < n && arr[right] > arr[largest])
        largest = right;

    if(largest != i){
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n){
    for(int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for(int i = n-1; i > 0; i--){
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

int main(){
    int n;

    printf("Enter number of elements: ");
    scanf("%d",&n);

    int arr[n];

    printf("Enter elements:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&arr[i]);

    heapSort(arr,n);

    printf("Sorted array:\n");
    for(int i=0;i<n;i++)
        printf("%d ",arr[i]);

    return 0;
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 

CREATE TABLE Area (
 aid INT PRIMARY KEY,
 aname VARCHAR(20),
 area_type VARCHAR(5)
);

CREATE TABLE Person (
 pno INT PRIMARY KEY,
 pname VARCHAR(20),
 birthdate DATE,
 income MONEY,
 aid INT REFERENCES Area(aid)
);

//INSERT VALUES 

INSERT INTO Area VALUES
(1,'Pune','urban'),
(2,'Village','rural');

INSERT INTO Person VALUES
(101,'Om','2000-01-01',50000,1),
(102,'Amit','1999-02-02',40000,2),
(103,'Ravi','2001-03-03',60000,1);

//TRIGGER

CREATE OR REPLACE FUNCTION delete_msg()
RETURNS trigger AS $$
BEGIN
 RAISE NOTICE 'Person record is being deleted';
 RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_delete
BEFORE DELETE ON Person
FOR EACH ROW
EXECUTE FUNCTION delete_msg();

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE max_min(a INT,b INT,c INT)
AS $$
DECLARE mx INT;
mn INT;
BEGIN
 mx := GREATEST(a,b,c);
 mn := LEAST(a,b,c);

 RAISE NOTICE 'Maximum: %', mx;
 RAISE NOTICE 'Minimum: %', mn;
END;
$$ LANGUAGE plpgsql;