
### 1. Instruction Set Format

To write machine code, your architecture's rules must map into a single 16-bit word. We break this down into three distinct parts:

* **Bits 15-12 (Top Nibble):** Destination Register Selector
* **Bits 11-8 (Middle Nibble):** ALU Operation Code (Opcode)
* **Bits 7-0 (Bottom Byte):** Immediate Data Value

### 2. Architecture Reference Tables

**Destination Registers (Bits 15-12)**

| Register | Hex Code | Binary |
| --- | --- | --- |
| NONE | `0x0` | `0000` |
| SELECT A | `0x1` | `0001` |
| SELECT B | `0x2` | `0010` |

**ALU Operations (Bits 11-8)**

| Operation | Hex Code | Binary |
| --- | --- | --- |
| ADD | `0x0` | `0000` |
| SUB | `0x1` | `0001` |
| MULT | `0x2` | `0010` |
| DIV | `0x3` | `0011` |
| AND | `0x4` | `0100` |
| OR | `0x5` | `0101` |
| LSHIFT | `0x6` | `0110` |
| RSHIFT | `0x7` | `0111` |

---

### 3. Example Machine Code Programs

Here are two programs you can manually type directly into your Logisim ROM.

**Program 1: Basic Arithmetic (Multiplication)**
This program loads 10 into A, 2 into B, and multiplies them.

1. **`100A`**: Load `0x0A` (Decimal 10) into A. *(Dest: 1, Opcode: 0, Data: 0A)*
2. **`2002`**: Load `0x02` (Decimal 2) into B. *(Dest: 2, Opcode: 0, Data: 02)*
3. **`0200`**: Execute MULT. *(Dest: 0, Opcode: 2, Data: 00)*
* *Result:* The final ALU output wire will display `0x14` (Decimal 20). Target `0` ensures you do not overwrite your registers with the dummy data.



**Program 2: Bitwise Logic**
This program tests your hardware logic and shift operations.

1. **`10FF`**: Load `0xFF` (Binary `11111111`) into A. *(Dest: 1, Op: 0, Data: FF)*
2. **`200F`**: Load `0x0F` (Binary `00001111`) into B. *(Dest: 2, Op: 0, Data: 0F)*
3. **`0400`**: Execute AND. *(Dest: 0, Op: 4, Data: 00)*
* *Result:* The ALU output wire will display `0x0F`.


4. **`0600`**: Execute LSHIFT. *(Dest: 0, Op: 6, Data: 00)*
* *Result:* Assuming your shifter shifts A by the lower bits of B, the final wire will update to reflect the shift.



