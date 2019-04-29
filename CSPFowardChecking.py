import argparse
import time
import datetime
from _sqlite3 import Row
from random import choice, randint
global nodes_expanded
import copy


nodes_expanded=0

'''
Read the sudoku puzzle from file and parse it to generate
2d list with 0 representing -
'''
n=0
m=0
k=0
def read_puzzle(filename):
    
    global n
    global k
    #global k
    
    puzzle_rows = []
    first_row= []
    int_first_row=[]
    with open(filename) as f:
        
        for line in f:
            line = line[:-1]
            first_row=line.strip().split()
            break
        
        for s in first_row:
            int_first_row.append(int(s))
            
        n=int_first_row[0]
        k=int_first_row[1]
       
        
        for line in f:
            line=line.strip('\n')
            puzzle_rows.append(line.split(' '))

    for row in range(0,n):
        for col in range(0,n): 
            if puzzle_rows[row][col]=='0':
                puzzle_rows[row][col]=0
            else:
                puzzle_rows[row][col]=int(puzzle_rows[row][col]) 

    return puzzle_rows



   
'''
check if we have any unallocated cell in the board
'''
def checkForUnallocatedCell(puzzle):
    
    v=0
    numrows=0
    numcols=0
    for i, x in enumerate(puzzle):
        if v in x:
            numrows=i
            numcols=x.index(v)
            return True,numrows,numcols
        
    return False,numrows,numcols

'''
check if we can allocate a particular number to the specified row and column of the board
'''
def canAllocate(puzzle, numrows, numcols, number):  
    if(isPresentRow(puzzle, numrows, numcols, number)==True):
        return False 
    if isPresentColumn(puzzle, numrows, numcols, number)==True:
        return False 
    #if ispresentBox(puzzle, numrows - numrows%m , numcols - numcols%k, number)==True:
    #    return False
           
    return True

'''
check if number is present in the row
'''
def isPresentRow(puzzle, numrows, numcols, number):
    
    row=puzzle[numrows]
    for r in row:
        if r == number:
            return True
    return False
 
'''
retrieve column list
'''
def columnList(matrix, i):
    return [row[i] for row in matrix]

'''
check if the given number is present in the column
'''
def isPresentColumn(puzzle, numrows, numcols, number):
    
    cols=[]
    cols=columnList(puzzle, numcols)
    
    for c in cols:
        if c == number:
            return True
    return False



'''
calculate the cell with minimum restricted value 
'''
def findMRV(puzzle):        
            
    global n     
    minCount = n+1    
    r=0
    c=0
    
    for row in range(0,n):
        for col in range(0,n):
            if puzzle[row][col] == 0:
                cell = (row,col)                            
                legit_domain = findLegitDomain(puzzle, cell)                
                if len(legit_domain) < minCount :
                    minCount = len(legit_domain)
                    r = row 
                    c = col                                            
    
    return r,c

'''
list of values allowed for the given cell
'''
def findLegitDomain(puzzle, cell):
    
    global n
    global k
    allowed_nums = []
    
    for number in range(1,k+1):
        if canAllocate(puzzle, cell[0], cell[1], number) == True:
            allowed_nums.append(number)
            
    return allowed_nums

'''
Impl of backtraking with MRV + forward checking
'''
def backtrackingMRVfwd(filename):
    ###
    # use backtracking +MRV + forward propogation
    # to solve sudoku puzzle here,
    # return the solution in the form of list of 
    # list as describe in the PDF with # of consistency
    # checks done
    ###
    global nodes_expanded
    nodes_expanded=0
    puzzle = read_puzzle(filename)
    
    back_track_MRV_fwd(puzzle) 
    
    return (puzzle, nodes_expanded)

'''
Recurse Impl of backtraking with MRV + forward checking
'''
def back_track_MRV_fwd(puzzle):
    
    global nodes_expanded
    global n
    global k
    isFree,numrows,numcols=checkForUnallocatedCell(puzzle)
    if not isFree:
        return True
    
    row,col = findMRV(puzzle)
    
    for number in range(1,k+1):
        if canAllocate(puzzle, row, col, number):
            puzzle[row][col] = number                
                        
            if forwardCheck(puzzle,row,col) == False:
                puzzle[row][col] = 0
                continue
            
            nodes_expanded= nodes_expanded+1
            
            if back_track_MRV_fwd(puzzle):
                return True
            
            puzzle[row][col] = 0
        
    return False

'''
do forward checking by checking for any cell with no legal values
'''     
def forwardCheck(puzzle,row,col):
            
    global n
    for i in range(0,n):
        if puzzle[row][i] == 0:
            nCell = (row,i)
            if not findLegitDomain(puzzle, nCell):
                return False
            
        if puzzle[i][col] == 0:
            nCell = (i,col)
            if not findLegitDomain(puzzle, nCell):
                return False

    return True

'''
Impl of backtraking with MRV + constraint propagation
'''            
def backtrackingMRVcp(filename):
    ###
    # use backtracking + MRV + cp to solve sudoku puzzle here,
    # return the solution in the form of list of 
    # list as describe in the PDF with # of consistency
    # checks done
    ###
    global nodes_expanded
    nodes_expanded=0
    puzzle = read_puzzle(filename)
    
    back_track_MRV_cp(puzzle) 
    
    return (puzzle, nodes_expanded)

'''
Recurse Impl of backtraking with MRV + constraint propagation
'''    
def back_track_MRV_cp(puzzle):
 
    global nodes_expanded
    global n
    global k
    isFree,numrows,numcols=checkForUnallocatedCell(puzzle)
    if not isFree:
        return True
    
    row,col = findMRV(puzzle)
    
    for number in range(1,k+1):
        if canAllocate(puzzle, row, col, number):
            puzzle[row][col] = number
            
            if arc_consistent(puzzle, row, col) == False:
                puzzle[row][col] = 0
                continue
            
            nodes_expanded= nodes_expanded+1
            
            if back_track_MRV_cp(puzzle):
                return True
            
            puzzle[row][col] = 0
            
    return False

'''
verify the arc consistency
'''    
def arc_consistent(puzzle, row, col):        
    
    if forwardCheck(puzzle,row,col) == False:
        return False
    
    global n
    global k
    for i in range(0,n):
        if puzzle[row][i] == 0:
            
            domainCount=0 
            invalidValues=0           
            for number in range(1,k+1): 
                if canAllocate(puzzle, row, i, number):
                    domainCount = domainCount + 1
                    nPuzzle = copy.deepcopy(puzzle)
                    nPuzzle[row][i]=number
                    if forwardCheck(nPuzzle,row,i) == False:
                        invalidValues = invalidValues + 1
                        
            if domainCount == invalidValues:
                return False                       
            
        if puzzle[i][col] == 0:  
            
            domainCount=0 
            invalidValues=0
            for number in range(1,k+1): 
                if canAllocate(puzzle, i, col, number):
                    domainCount = domainCount + 1
                    nPuzzle = copy.deepcopy(puzzle)
                    nPuzzle[i][col]=number
                    if forwardCheck(nPuzzle,i,col) == False:
                        invalidValues = invalidValues + 1
                        
            if domainCount == invalidValues:
                return False 
            
    return True

'''
Sudoku solver using minimum conflict technique
'''
def minConflict(filename):
    ###
    # use minConflict to solve sudoku puzzle here,
    # return the solution in the form of list of 
    # list as describe in the PDF with # of consistency
    # checks done
    ###
    
    global nodes_expanded
    global n
    nodes_expanded=0
    puzzle = read_puzzle(filename)
    initialValues=[]
    
    for row in range(0,n):
        for col in range(0,n): 
            if puzzle[row][col]==0:
                puzzle[row][col]=randint(1,n)
            else:
                cell=(row,col)
                initialValues.append(cell) 
                
    min_Conflict(puzzle, initialValues)
    
    return (puzzle, nodes_expanded)
    
'''
Impl Sudoku solver using minimum conflict technique
'''
def min_Conflict(puzzle, initialValues, numIter=20000):
    
    global nodes_expanded
    global n

    for i in range(1,numIter+1):
        
        conflictedCells=[]
    
        if goalState(puzzle):
            return True
        
        for row in range(0,n):
            for col in range(0,n):
                cel=(row,col)
                if cel in initialValues:
                    continue
                
                temp=puzzle[row][col]
                puzzle[row][col]=0
                if not canAllocate(puzzle, row, col, temp):
                    cell=(row,col)
                    puzzle[row][col]=temp
                    conflictedCells.append(cell)
                else:
                    puzzle[row][col]=temp
        
        if not conflictedCells:
            return True
            
        randomCell= choice(conflictedCells)
        minCount=n+1   
        num=0
        
        for i in range(1,n+1):            
            count=countConflict(puzzle, randomCell[0], randomCell[1], i)
            if(count<minCount):
                minCount=count
                num=i                            
        
        nodes_expanded = nodes_expanded + 1            
        puzzle[randomCell[0]][randomCell[1]]=num
        
    return False

'''
count the number of conflicts for a cell
'''
def countConflict(puzzle, numrows, numcols, number):
    count=0
    
    if(isPresentRow(puzzle, numrows, numcols, number)==True):
        count=count+1;
    
    if isPresentColumn(puzzle, numrows, numcols, number)==True:
        count=count+1;
         
    #if ispresentBox(puzzle, numrows - numrows%m , numcols - numcols%k, number)==True:
        #count=count+1;
           
    return count

'''
check if the board has reached to the goal state
'''
def goalState(puzzle):
    
    for row in range(0,n):
            for col in range(0,n):
                temp=puzzle[row][col]
                puzzle[row][col]=0
                if canAllocate(puzzle, row, col, temp):
                    puzzle[row][col]=temp
                    continue
                else:
                    puzzle[row][col]=temp
                    return False
                                
    return True

def main(args):
    
    ##########################################################
    # backtracking + MRV + fwd
    ##########################################################
    tic =  datetime.datetime.now()
    solution, consistencyChecks = backtrackingMRVfwd(args.input)
    toc =  datetime.datetime.now()
    timeItr = toc - tic
    file_name = "CSPMRVFowardChecking_solution.txt"
    length = len(solution)
    s=""
    for i in range(length):
        for j in range(length):
            s += str(solution[i][j])+' '
        s+='\n'
    print(s)
    with open (file_name,'w',encoding = "utf-8") as file1:
        file1.write(str((timeItr).total_seconds())+'s'+'\n')
        file1.write(s+'\n')

    # backtracking + MRV + CP

    tic =  datetime.datetime.now()
    solution, consistencyChecks = backtrackingMRVcp(args.input)
    toc =  datetime.datetime.now()
    timeItr = toc - tic
    
    file_name = "CSPMRV_CP_solution.txt"
    length = len(solution)
    s=""
    for i in range(length):
        for j in range(length):
            s += str(solution[i][j])+' '
        s+='\n'
    print(s)
    with open (file_name,'w',encoding = "utf-8") as file1:
        file1.write(str((timeItr).total_seconds())+'s'+'\n')
        file1.write(s+'\n')

    tic = datetime.datetime.now()
    solution, consistencyChecks = minConflict(args.input)
    toc = datetime.datetime.now()
    timeItr = toc - tic
    
    print ("minConflict:")
    print ("Execution Time: " + str(timeItr.total_seconds()))
    print ("Consistency Checks: " + str(consistencyChecks))
    print ("Solution: " + str(solution) + '\n')
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="HomeWork Three")
    parser.add_argument("--input", default="game1.txt",type=str)
    args = parser.parse_args()
    main(args)
