library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;

entity fetch is
	port
	(
		CLK_FT : in std_logic;
		P_COUNT : in std_logic_vector(7 downto 0);
		PROM_OUT : out std_logic_vector(14 downto 0)
	);
end fetch;

architecture RTL of fetch is

subtype WORD is std_logic_vector(14 downto 0);
type MEMORY is array(0 to 15) of WORD;

constant MEM : MEMORY :=
	(
	"100100000000000",
	"100000000000000",
	"100100100000000",
	"100000100000001",
	"100101000000000",
	"100001000000000",
	"100101100000000",
	"100001100001010",
	"000101000100000",
	"000100001000000",
	"111000001000000",
	"101001001100000",
	"101100000001110",
	"110000000001000",
	"111100000000000",
	"000000000000000"
	);
	
begin
	process(CLK_FT)
	begin
		if(CLK_FT'event and CLK_FT = '1') then
			PROM_OUT <= MEM(conv_integer(P_COUNT(3 downto 0)));
		end if;
	end process;
end RTL;
	