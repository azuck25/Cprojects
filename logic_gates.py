'''
The following program creates the logic
that defines the building blocks of 
the common logic gates found in circuits
'''

from operator import xor


class LogicGate:

    def __init__(self,n,x1,x2):
        self.input1 = x1
        self.input2 = x2
        self.name = n
        self.output = None

    def getLabel(self):
        return self.name

    def getOutput(self):
        self.output = self.performGateLogic()
        return self.output
        

#Binary gate with two input lines    and, or , nand, xor, etc
class BinaryGate(LogicGate):

    def __init__(self, n, x1, x2):
        super(BinaryGate, self).__init__(n,x1,x2)
        self.pinA = None
        self.pinB = None

    def getPinA(self):
        if self.pinA == None:
            return self.input1
        else:
            return self.pinA.getFrom().getOutput() 

    def getPinB(self):
        if self.pinB == None:
            return self.input2
        else:
            return self.pinB.getFrom().getOutput()

    def setNextPin(self,source):
        if self.pinA == None:
            self.pinA = source
        elif self.pinB == None:
            self.pinB = source
        else:
            print("There are no pins available on this binary gate\n Cant Connect.")


class UnaryGate(LogicGate):

    def __init__(self, n):
        LogicGate.__init__(self, n)
        self.pin = None

    def getPin(self):
        if self.pin == None:
            return int(input("Enter Pin input for gate " + self.getLabel()+":"))
        else:
            return self.pin.getFrom().getOutput()

    def setNextPin(self, source):
        if self.pin == None:
            self.pin = source
        else:
            print("Cant connect")

    
class AndGate(BinaryGate):

    def __init__(self,n,x1,x2):
        super(AndGate, self).__init__(n,x1,x2)
    
    def performGateLogic(self):
        
        a = self.getPinA()
        b = self.getPinB()

        if a == 1 and b == 1:
            return 1
        else:
            return 0


class OrGate(BinaryGate):

    def __init__(self, n,x1,x2):
        super(OrGate, self).__init__(n,x1,x2)
    
    def performGateLogic(self):

        a = self.getPinA()
        b = self.getPinB()

        if a == 1 or b == 1:
            return 1
        else:
            return 0

class NandGate(BinaryGate):

    def __init__(self, n, x1,x2):
        super().__init__(n,x1,x2)
    
    def performGateLogic(self):

        a = self.getPinA()
        b = self.getPinB()

        if a == 1 and b == 1:
            return 0
        else:
            return 1

class NorGate(BinaryGate):

    def __init__(self, n,x1,x2):
        super().__init__(n,x1,x2)

    def performGateLogic(self):

        a = self.getPinA()
        b = self.getPinB()

        if a == 0 and b == 0:
            return 1
        else:
            return 0

class XorGate(BinaryGate):

    def __init__(self, n,x1,x2):
        super().__init__(n,x1,x2)

    def performGateLogic(self):

        a = self.getPinA()
        b = self.getPinB()

        if (a == 1 and b == 0) or (a == 0 and b == 1):
            return 1
        else:
            return 0
        
class notGate(UnaryGate):

    def __init__(self, n):
        super(notGate, self).__init__(n)

    def performGateLogic(self):
        a = self.getPin()
        
        if a == 1:
            return 0
        else:
            return 1

class Connector:

    def __init__(self, fgate, tgate):

        self.fromgate = fgate
        self.togate = tgate

        tgate.setNextPin(self)

    def getFrom(self):
        return self.fromgate

    def getTo(self):
        return self.togate




def main():
    binary_string = str(input("Enter an 8 bit binary integer : "))
    binary_string1 = str(input("Enter a 8 bit binary integer : "))
    x = []
    y = []
    count = len(binary_string) - 1
    
    carry = [0,0,0,0,0,0,0,0,0]
    sum_v = []

    
    while count >= 0:
        x.append(ord(binary_string[count]) - ord('0'))
        y.append(ord(binary_string1[count]) - ord('0'))
        count -= 1

    g1 = AndGate("G1",x[0],y[0])
    g2 = OrGate("G2",g1.getOutput(),y[0])
    count1 = 1
    carry[0] = g2.getOutput()

    while count1 < 8:
        A = AndGate(f"A{count1}",x[count1],y[count1])
        B = AndGate(f"B{count1}",x[count1],carry[count1 - 1])
        C = OrGate(f"C{count1}",A.getOutput(),B.getOutput())
        D = OrGate(f"D{count1}",C.getOutput(),y[count1])
        carry[count1] = D.getOutput()
        print("A : ",x[count1],"&",y[count1]," : ",A.getOutput(), "\n")
        print("B : ",x[count1],"&",carry[count1 - 1], " : ",B.getOutput(), "\n")
        print("C : ",A.getOutput(),"+",B.getOutput()," : ",C.getOutput(), "\n")
        print("D : ",C.getOutput(),"+",y[count1]," : ",D.getOutput(), "\n\n\n")
        count1 += 1
        
    print(*carry,"\n\n")
    count1 = 0

    while count1 < 8:
        A = XorGate(f"A{count1}",x[count1],y[count1])
        B = XorGate(f"B{count}",A.getOutput(),carry[count1 -1])
        sum_v.append(B.getOutput())
        print("A : ",x[count1]," XOR ",y[count1]," : ",A.getOutput())
        print("B : ",A.getOutput()," XOR ",carry[count1 -1], " : ",B.getOutput(),"\n")
        count1 += 1

    print("\n\n")
    j = 0
       
    for i in sum_v:
        print(i," at index : ", j)
        j += 1

    print("\n\n",*sum_v[::-1])

    #Full Adder Circuit : Cᵢ₊₁ = Xᵢ*Yᵢ + Xᵢ*Cᵢ + Yᵢ
    #                     Sᵢ = Xᵢ xor Yᵢ xor Cᵢ
    # 8 bit number 10110110


   



main()