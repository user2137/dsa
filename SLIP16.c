//SLIP - 16
//Q.1
#include <stdio.h>

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n-1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    int arr[n];
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
CREATE TABLE Student (
 rollno INT PRIMARY KEY,
 name VARCHAR(30),
 address VARCHAR(50),
 class VARCHAR(10)
);

CREATE TABLE Subject (
 scode VARCHAR(10) PRIMARY KEY,
 subject_name VARCHAR(20)
);

-- M-M RELATION
CREATE TABLE Student_Subject (
 rollno INT REFERENCES Student(rollno),
 scode VARCHAR(10) REFERENCES Subject(scode),
 marks_scored INT,
 PRIMARY KEY(rollno, scode)
);

//INSERT VALUES 

INSERT INTO Student VALUES
(1,'Om','Pune','SY'),
(2,'Amit','Mumbai','FY');

INSERT INTO Subject VALUES
('S1','DBMS'),
('S2','DS');

INSERT INTO Student_Subject VALUES
(1,'S1',80),
(1,'S2',70),
(2,'S1',60),
(2,'S2',50);

//TRIGGER
CREATE OR REPLACE FUNCTION delete_student_msg()
RETURNS trigger AS $$
BEGIN
 RAISE NOTICE 'student record is being deleted';
 RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_student
BEFORE DELETE ON Student
FOR EACH ROW
EXECUTE FUNCTION delete_student_msg();

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
