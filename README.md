# gamedev_task3

Task 3. Overloading


Continue working with the matrix class from the previous PT. The class must have the following properties:

Contain overloaded operations (+, -, *, / ), which provide:

diagnostics of the possibility of performing an operation;

diagnostics of possible overflow (only for + and -);

commutativity (a + b = b + a);

chaining operations (d = a + b + c);

for the operation “/” the analysis of the divisor by equality to zero (in this case, you can return the result = 0);

Contain overloaded operations (+ =), (– =), (* =), (/ =) and provide:

diagnostics of possible overflow (for += and -=);

chaining operations;

execution of operations when the second operand is directly specified (d + = 3).

For overloaded operations (+, -, *, / ) implement:

execution with a directly specified constant or character string (d=a+”222”+b+111+c).

Contain overloaded relational operations (>), (<), (>=), (<=) and equality checks (==), (!=).

Explanation: comparison operations compare the sums of matrix elements..
