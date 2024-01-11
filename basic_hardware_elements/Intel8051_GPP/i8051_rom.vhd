-- test/sort.hex 

library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_ARITH.all;
use WORK.I8051_LIB.all;

entity I8051_ROM is
    port(rst      : in  STD_LOGIC;
         clk      : in  STD_LOGIC;
         addr     : in  UNSIGNED (11 downto 0);
         data     : out UNSIGNED (7 downto 0);
         rd       : in  STD_LOGIC);
end I8051_ROM;

architecture BHV of I8051_ROM is

    type ROM_TYPE is array (0 to 541) of UNSIGNED (7 downto 0);

    constant PROGRAM : ROM_TYPE := (

	"00000010",	-- LJMP   
	"00000000",
	"11001010",
	"10001011",	-- MOV_9  
	"00010010",
	"10001010",	-- MOV_9  
	"00010011",
	"10001001",	-- MOV_9  
	"00010100",
	"10001101",	-- MOV_9  
	"00010101",
	"11100100",	-- CLR_1  
	"11111111",	-- MOV_5  
	"11101111",	-- MOV_1  
	"11000011",	-- CLR_2  
	"10010101",	-- SUBB_2 
	"00010101",
	"01010000",	-- JNC    
	"01000110",
	"10101110",	-- MOV_6  
	"00000111",
	"11101110",	-- MOV_1  
	"11000011",	-- CLR_2  
	"10010101",	-- SUBB_2 
	"00010101",
	"01010000",	-- JNC    
	"00111011",
	"10101011",	-- MOV_6  
	"00010010",
	"10101010",	-- MOV_6  
	"00010011",
	"10101001",	-- MOV_6  
	"00010100",
	"10001110",	-- MOV_9  
	"10000010",
	"01110101",	-- MOV_12 
	"10000011",
	"00000000",
	"00010010",	-- LCALL  
	"00000001",
	"11001111",
	"11111101",	-- MOV_5  
	"10001111",	-- MOV_9  
	"10000010",
	"01110101",	-- MOV_12 
	"10000011",
	"00000000",
	"00010010",	-- LCALL  
	"00000001",
	"11001111",
	"11111100",	-- MOV_5  
	"11010011",	-- SETB_1 
	"10011101",	-- SUBB_1 
	"01000000",	-- JC     
	"00011100",
	"10001100",	-- MOV_9  
	"00010110",
	"10001110",	-- MOV_9  
	"10000010",
	"01110101",	-- MOV_12 
	"10000011",
	"00000000",
	"00010010",	-- LCALL  
	"00000001",
	"11001111",
	"10001111",	-- MOV_9  
	"10000010",
	"01110101",	-- MOV_12 
	"10000011",
	"00000000",
	"00010010",	-- LCALL  
	"00000001",
	"11111100",
	"10001110",	-- MOV_9  
	"10000010",
	"01110101",	-- MOV_12 
	"10000011",
	"00000000",
	"11100101",	-- MOV_2  
	"00010110",
	"00010010",	-- LCALL  
	"00000001",
	"11111100",
	"00001110",	-- INC_2  
	"10000000",	-- SJMP   
	"10111111",
	"00001111",	-- INC_2  
	"10000000",	-- SJMP   
	"10110100",
	"11100100",	-- CLR_1  
	"11110101",	-- MOV_8  
	"10000000",
	"00100010",	-- RET    
	"10001011",	-- MOV_9  
	"00010010",
	"10001010",	-- MOV_9  
	"00010011",
	"10001001",	-- MOV_9  
	"00010100",
	"10001101",	-- MOV_9  
	"00010101",
	"11100100",	-- CLR_1  
	"11110101",	-- MOV_8  
	"00010110",
	"10101101",	-- MOV_6  
	"00010110",
	"11101101",	-- MOV_1  
	"00110011",	-- RLC    
	"10010101",	-- SUBB_2 
	"11100000",
	"11111100",	-- MOV_5  
	"11000011",	-- CLR_2  
	"11101101",	-- MOV_1  
	"10010101",	-- SUBB_2 
	"00010101",
	"01110100",	-- MOV_4  
	"10000000",
	"11111000",	-- MOV_5  
	"01101100",	-- XRL_1  
	"10011000",	-- SUBB_1 
	"01010000",	-- JNC    
	"00011001",
	"10101011",	-- MOV_6  
	"00010010",
	"10101010",	-- MOV_6  
	"00010011",
	"10101001",	-- MOV_6  
	"00010100",
	"10101111",	-- MOV_6  
	"00010110",
	"11101111",	-- MOV_1  
	"00110011",	-- RLC    
	"10010101",	-- SUBB_2 
	"11100000",
	"10001111",	-- MOV_9  
	"10000010",
	"11110101",	-- MOV_8  
	"10000011",
	"00010010",	-- LCALL  
	"00000001",
	"11001111",
	"11110101",	-- MOV_8  
	"10000000",
	"00000101",	-- INC_3  
	"00010110",
	"10000000",	-- SJMP   
	"11010101",
	"00100010",	-- RET    
	"01111000",	-- MOV_7  
	"00001000",
	"01111100",	-- MOV_7  
	"00000000",
	"01111101",	-- MOV_7  
	"00000000",
	"01111011",	-- MOV_7  
	"11111111",
	"01111010",	-- MOV_7  
	"00000000",
	"01111001",	-- MOV_7  
	"11000000",
	"01111110",	-- MOV_7  
	"00000000",
	"01111111",	-- MOV_7  
	"00001010",
	"00010010",	-- LCALL  
	"00000001",
	"10100110",
	"01111011",	-- MOV_7  
	"00000000",
	"01111010",	-- MOV_7  
	"00000000",
	"01111001",	-- MOV_7  
	"00001000",
	"01111101",	-- MOV_7  
	"00001010",
	"00010010",	-- LCALL  
	"00000000",
	"00000011",
	"01111011",	-- MOV_7  
	"00000000",
	"01111010",	-- MOV_7  
	"00000000",
	"01111001",	-- MOV_7  
	"00001000",
	"01111101",	-- MOV_7  
	"00001010",
	"00010010",	-- LCALL  
	"00000000",
	"01011101",
	"10000000",	-- SJMP   
	"11111110",
	"00100010",	-- RET    
	"00010011",	-- RRC    
	"00010010",	-- LCALL  
	"00010001",
	"00010000",
	"00001111",	-- INC_2  
	"00001110",	-- INC_2  
	"00001101",	-- INC_2  
	"00001100",	-- INC_2  
	"00001011",	-- INC_2  
	"00001010",	-- INC_2  
	"01111000",	-- MOV_7  
	"01111111",
	"11100100",	-- CLR_1  
	"11110110",	-- MOV_13 
	"11011000",	-- DJNZ_1 
	"11111101",
	"01110101",	-- MOV_12 
	"10000001",
	"00010110",
	"00000010",	-- LJMP   
	"00000000",
	"10010100",
	"11100111",	-- MOV_3  
	"00001001",	-- INC_2  
	"11110110",	-- MOV_13 
	"00001000",	-- INC_2  
	"11011111",	-- DJNZ_1 
	"11111010",
	"10000000",	-- SJMP   
	"01000110",
	"11100111",	-- MOV_3  
	"00001001",	-- INC_2  
	"11110010",	-- MOVX_3 
	"00001000",	-- INC_2  
	"11011111",	-- DJNZ_1 
	"11111010",
	"10000000",	-- SJMP   
	"00111110",
	"10001000",	-- MOV_9  
	"10000010",
	"10001100",	-- MOV_9  
	"10000011",
	"11100111",	-- MOV_3  
	"00001001",	-- INC_2  
	"11110000",	-- MOVX_4 
	"10100011",	-- INC_5  
	"11011111",	-- DJNZ_1 
	"11111010",
	"10000000",	-- SJMP   
	"00110010",
	"11100011",	-- MOVX_1 
	"00001001",	-- INC_2  
	"11110110",	-- MOV_13 
	"00001000",	-- INC_2  
	"11011111",	-- DJNZ_1 
	"11111010",
	"10000000",	-- SJMP   
	"01111000",
	"11100011",	-- MOVX_1 
	"00001001",	-- INC_2  
	"11110010",	-- MOVX_3 
	"00001000",	-- INC_2  
	"11011111",	-- DJNZ_1 
	"11111010",
	"10000000",	-- SJMP   
	"01110000",
	"10001000",	-- MOV_9  
	"10000010",
	"10001100",	-- MOV_9  
	"10000011",
	"11100011",	-- MOVX_1 
	"00001001",	-- INC_2  
	"11110000",	-- MOVX_4 
	"10100011",	-- INC_5  
	"11011111",	-- DJNZ_1 
	"11111010",
	"10000000",	-- SJMP   
	"01100100",
	"10001001",	-- MOV_9  
	"10000010",
	"10001010",	-- MOV_9  
	"10000011",
	"11100000",	-- MOVX_2 
	"10100011",	-- INC_5  
	"11110110",	-- MOV_13 
	"00001000",	-- INC_2  
	"11011111",	-- DJNZ_1 
	"11111010",
	"10000000",	-- SJMP   
	"01011000",
	"10001001",	-- MOV_9  
	"10000010",
	"10001010",	-- MOV_9  
	"10000011",
	"11100000",	-- MOVX_2 
	"10100011",	-- INC_5  
	"11110010",	-- MOVX_3 
	"00001000",	-- INC_2  
	"11011111",	-- DJNZ_1 
	"11111010",
	"10000000",	-- SJMP   
	"01001100",
	"10000000",	-- SJMP   
	"11010010",
	"10000000",	-- SJMP   
	"11111010",
	"10000000",	-- SJMP   
	"11000110",
	"10000000",	-- SJMP   
	"11010100",
	"10000000",	-- SJMP   
	"01101001",
	"10000000",	-- SJMP   
	"11110010",
	"10000000",	-- SJMP   
	"00110011",
	"10000000",	-- SJMP   
	"00010000",
	"10000000",	-- SJMP   
	"10100110",
	"10000000",	-- SJMP   
	"11101010",
	"10000000",	-- SJMP   
	"10011010",
	"10000000",	-- SJMP   
	"10101000",
	"10000000",	-- SJMP   
	"11011010",
	"10000000",	-- SJMP   
	"11100010",
	"10000000",	-- SJMP   
	"11001010",
	"10000000",	-- SJMP   
	"00110011",
	"10001001",	-- MOV_9  
	"10000010",
	"10001010",	-- MOV_9  
	"10000011",
	"11101100",	-- MOV_1  
	"11111010",	-- MOV_5  
	"11100100",	-- CLR_1  
	"10010011",	-- MOVC_1 
	"10100011",	-- INC_5  
	"11001000",	-- XCH_1  
	"11000101",	-- XCH_2  
	"10000010",
	"11001000",	-- XCH_1  
	"11001100",	-- XCH_1  
	"11000101",	-- XCH_2  
	"10000011",
	"11001100",	-- XCH_1  
	"11110000",	-- MOVX_4 
	"10100011",	-- INC_5  
	"11001000",	-- XCH_1  
	"11000101",	-- XCH_2  
	"10000010",
	"11001000",	-- XCH_1  
	"11001100",	-- XCH_1  
	"11000101",	-- XCH_2  
	"10000011",
	"11001100",	-- XCH_1  
	"11011111",	-- DJNZ_1 
	"11101001",
	"11011110",	-- DJNZ_1 
	"11100111",
	"10000000",	-- SJMP   
	"00001101",
	"10001001",	-- MOV_9  
	"10000010",
	"10001010",	-- MOV_9  
	"10000011",
	"11100100",	-- CLR_1  
	"10010011",	-- MOVC_1 
	"10100011",	-- INC_5  
	"11110110",	-- MOV_13 
	"00001000",	-- INC_2  
	"11011111",	-- DJNZ_1 
	"11111001",
	"11101100",	-- MOV_1  
	"11111010",	-- MOV_5  
	"10101001",	-- MOV_6  
	"11110000",
	"11101101",	-- MOV_1  
	"11111011",	-- MOV_5  
	"00100010",	-- RET    
	"10001001",	-- MOV_9  
	"10000010",
	"10001010",	-- MOV_9  
	"10000011",
	"11101100",	-- MOV_1  
	"11111010",	-- MOV_5  
	"11100000",	-- MOVX_2 
	"10100011",	-- INC_5  
	"11001000",	-- XCH_1  
	"11000101",	-- XCH_2  
	"10000010",
	"11001000",	-- XCH_1  
	"11001100",	-- XCH_1  
	"11000101",	-- XCH_2  
	"10000011",
	"11001100",	-- XCH_1  
	"11110000",	-- MOVX_4 
	"10100011",	-- INC_5  
	"11001000",	-- XCH_1  
	"11000101",	-- XCH_2  
	"10000010",
	"11001000",	-- XCH_1  
	"11001100",	-- XCH_1  
	"11000101",	-- XCH_2  
	"10000011",
	"11001100",	-- XCH_1  
	"11011111",	-- DJNZ_1 
	"11101010",
	"11011110",	-- DJNZ_1 
	"11101000",
	"10000000",	-- SJMP   
	"11011011",
	"10001001",	-- MOV_9  
	"10000010",
	"10001010",	-- MOV_9  
	"10000011",
	"11100100",	-- CLR_1  
	"10010011",	-- MOVC_1 
	"10100011",	-- INC_5  
	"11110010",	-- MOVX_3 
	"00001000",	-- INC_2  
	"11011111",	-- DJNZ_1 
	"11111001",
	"10000000",	-- SJMP   
	"11001100",
	"10001000",	-- MOV_9  
	"11110000",
	"11101101",	-- MOV_1  
	"00100100",	-- ADD_4  
	"00000010",
	"10110100",	-- CJNE_2 
	"00000100",
	"00000000",
	"01010000",	-- JNC    
	"11000010",
	"11110101",	-- MOV_8  
	"10000010",
	"11101011",	-- MOV_1  
	"00100100",	-- ADD_4  
	"00000010",
	"10110100",	-- CJNE_2 
	"00000100",
	"00000000",
	"01010000",	-- JNC    
	"10111000",
	"00100011",	-- RL     
	"00100011",	-- RL     
	"01000101",	-- ORL_2  
	"10000010",
	"11110101",	-- MOV_8  
	"10000010",
	"11101111",	-- MOV_1  
	"01001110",	-- ORL_1  
	"01100000",	-- JZ     
	"10101110",
	"11101111",	-- MOV_1  
	"01100000",	-- JZ     
	"00000001",
	"00001110",	-- INC_2  
	"11100101",	-- MOV_2  
	"10000010",
	"00100011",	-- RL     
	"10010000",	-- MOV_18 
	"00000001",
	"00100110",
	"01110011",	-- JMP    
	"10111011",	-- CJNE_3 
	"00000001",
	"00001100",
	"11100101",	-- MOV_2  
	"10000010",
	"00101001",	-- ADD_1  
	"11110101",	-- MOV_8  
	"10000010",
	"11100101",	-- MOV_2  
	"10000011",
	"00111010",	-- ADDC_1 
	"11110101",	-- MOV_8  
	"10000011",
	"11100000",	-- MOVX_2 
	"00100010",	-- RET    
	"01010000",	-- JNC    
	"00000110",
	"11101001",	-- MOV_1  
	"00100101",	-- ADD_2  
	"10000010",
	"11111000",	-- MOV_5  
	"11100110",	-- MOV_3  
	"00100010",	-- RET    
	"10111011",	-- CJNE_3 
	"11111110",
	"00000110",
	"11101001",	-- MOV_1  
	"00100101",	-- ADD_2  
	"10000010",
	"11111000",	-- MOV_5  
	"11100010",	-- MOVX_1 
	"00100010",	-- RET    
	"11100101",	-- MOV_2  
	"10000010",
	"00101001",	-- ADD_1  
	"11110101",	-- MOV_8  
	"10000010",
	"11100101",	-- MOV_2  
	"10000011",
	"00111010",	-- ADDC_1 
	"11110101",	-- MOV_8  
	"10000011",
	"11100100",	-- CLR_1  
	"10010011",	-- MOVC_1 
	"00100010",	-- RET    
	"11111000",	-- MOV_5  
	"10111011",	-- CJNE_3 
	"00000001",
	"00001101",
	"11100101",	-- MOV_2  
	"10000010",
	"00101001",	-- ADD_1  
	"11110101",	-- MOV_8  
	"10000010",
	"11100101",	-- MOV_2  
	"10000011",
	"00111010",	-- ADDC_1 
	"11110101",	-- MOV_8  
	"10000011",
	"11101000",	-- MOV_1  
	"11110000",	-- MOVX_4 
	"00100010",	-- RET    
	"01010000",	-- JNC    
	"00000110",
	"11101001",	-- MOV_1  
	"00100101",	-- ADD_2  
	"10000010",
	"11001000",	-- XCH_1  
	"11110110",	-- MOV_13 
	"00100010",	-- RET    
	"10111011",	-- CJNE_3 
	"11111110",
	"00000101",
	"11101001",	-- MOV_1  
	"00100101",	-- ADD_2  
	"10000010",
	"11001000",	-- XCH_1  
	"11110010",	-- MOVX_3 
	"00100010");	-- RET    
begin

    process(rst, clk)
    begin
        if( rst = '1' ) then

            data <= CD_8;
        elsif( clk'event and clk = '1' ) then

            if( rd = '1' ) then

                data <= PROGRAM(conv_integer(addr));
            else

                data <= CD_8;
            end if;
        end if;
    end process;
end BHV;