* TINY Compilation to TM Code
* File: testcase1/test2e.tm
* Standard prelude:
  0:     LD  5,0(0) 	load gp with maxaddress
  1:    LDA  6,0(5) 	copy gp to mp
  2:     ST  0,0(0) 	clear location 0
* End of standard prelude.
* -> Function (main)
  4:     ST  1,-2(5) 	func: store the location of func. entry
* func: unconditional jump to next declaration belongs here
* func: function body starts here
  3:    LDC  1,6(0) 	func: load function location
  6:     ST  0,-1(6) 	func: store return address
* -> compound
* -> assign
* -> Id (i)
  7:    LDC  0,-2(0) 	id: load varOffset
  8:    ADD  0,6,0 	id: calculate the address
  9:    LDA  0,0(0) 	load id address
* <- Id
 10:     ST  0,-4(6) 	assign: push left (address)
* -> Const
 11:    LDC  0,0(0) 	load const
* <- Const
 12:     LD  1,-4(6) 	assign: load left (address)
 13:     ST  0,0(1) 	assign: store value
* <- assign
* -> assign
* -> Id (j)
 14:    LDC  0,-3(0) 	id: load varOffset
 15:    ADD  0,6,0 	id: calculate the address
 16:    LDA  0,0(0) 	load id address
* <- Id
 17:     ST  0,-4(6) 	assign: push left (address)
* -> Const
 18:    LDC  0,1(0) 	load const
* <- Const
 19:     LD  1,-4(6) 	assign: load left (address)
 20:     ST  0,0(1) 	assign: store value
* <- assign
* -> iter.
* while: jump after body comes back here
* -> Id (i)
 21:    LDC  0,-2(0) 	id: load varOffset
 22:    ADD  0,6,0 	id: calculate the address
 23:     LD  0,0(0) 	load id value
* <- Id
* while: jump to end belongs here
* -> compound
* -> assign
* -> Id (i)
 25:    LDC  0,0(0) 	id: load varOffset
 26:    ADD  0,5,0 	id: calculate the address
 27:    LDA  0,0(0) 	load id address
* <- Id
 28:     ST  0,-4(6) 	assign: push left (address)
* -> Op
* -> Id (i)
 29:    LDC  0,0(0) 	id: load varOffset
 30:    ADD  0,5,0 	id: calculate the address
 31:     LD  0,0(0) 	load id value
* <- Id
 32:     ST  0,-5(6) 	op: push left
* -> Const
 33:    LDC  0,1(0) 	load const
* <- Const
 34:     LD  1,-5(6) 	op: load left
 35:    ADD  0,1,0 	op +
* <- Op
 36:     LD  1,-4(6) 	assign: load left (address)
 37:     ST  0,0(1) 	assign: store value
* <- assign
* -> assign
* -> Id (j)
 38:    LDC  0,-1(0) 	id: load varOffset
 39:    ADD  0,5,0 	id: calculate the address
 40:    LDA  0,0(0) 	load id address
* <- Id
 41:     ST  0,-4(6) 	assign: push left (address)
* -> Op
* -> Id (j)
 42:    LDC  0,-1(0) 	id: load varOffset
 43:    ADD  0,5,0 	id: calculate the address
 44:     LD  0,0(0) 	load id value
* <- Id
 45:     ST  0,-5(6) 	op: push left
* -> Id (i)
 46:    LDC  0,0(0) 	id: load varOffset
 47:    ADD  0,5,0 	id: calculate the address
 48:     LD  0,0(0) 	load id value
* <- Id
 49:     LD  1,-5(6) 	op: load left
 50:    ADD  0,1,0 	op +
* <- Op
 51:     LD  1,-4(6) 	assign: load left (address)
 52:     ST  0,0(1) 	assign: store value
* <- assign
* <- compound
 53:    LDA  7,-33(7) 	while: jmp back to test
 24:    JEQ  0,29(7) 	while: jmp to end
* <- iter.
* -> Call
* -> Id (i)
 54:    LDC  0,-2(0) 	id: load varOffset
 55:    ADD  0,6,0 	id: calculate the address
 56:     LD  0,0(0) 	load id value
* <- Id
 57:     ST  0,-6(6) 	call: push argument
 58:     LD  0,-6(6) 	load arg to ac
 59:    OUT  0,0,0 	write ac
* <- Call
* -> Call
* -> Id (j)
 60:    LDC  0,-3(0) 	id: load varOffset
 61:    ADD  0,6,0 	id: calculate the address
 62:     LD  0,0(0) 	load id value
* <- Id
 63:     ST  0,-6(6) 	call: push argument
 64:     LD  0,-6(6) 	load arg to ac
 65:    OUT  0,0,0 	write ac
* <- Call
* <- compound
 66:     LD  7,-1(6) 	func: load pc with return address
  5:    LDA  7,61(7) 	func: unconditional jump to next declaration
* -> Function (main)
 67:    LDC  0,-1(0) 	init: load globalOffset
 68:    ADD  6,6,0 	init: initialize mp with globalOffset
* -> Call
 69:     ST  6,0(6) 	call: store current mp
 70:    LDA  6,0(6) 	call: push new frame
 71:    LDA  0,1(7) 	call: save return in ac
 72:    LDC  7,6(0) 	call: unconditional jump to main() entry
 73:     LD  6,0(6) 	call: pop current frame
* <- Call
* End of execution.
 74:   HALT  0,0,0 	
