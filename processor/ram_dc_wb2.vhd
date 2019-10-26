library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;

entity ram_dc_wb2 is
	port(
		CLK : in std_logic;
		RAM_ADDR : in std_logic_vector(7 downto 0);
		RAM_IN : in std_logic_vector(15 downto 0);
		IO65_IN : in std_logic_vector(15 downto 0);
		RAM_WEN : in std_logic;
		RAM_OUT : out std_logic_vector(15 downto 0);
		IO64_OUT : out std_logic_vector(15 downto 0)
	);
end ram_dc_wb2;

architecture RTL of ram_dc_wb2 is
subtype RAM_WORD is std_logic_vector(15 downto 0);
type RAM_ARRAY_TYPE is array(0 to 63) of RAM_WORD;
signal RAM_ARRAY : RAM_ARRAY_TYPE;
signal RAM_ADDR_DLY : std_logic_vector(7 downto 0);
signal RAM_ADDR_DLY2 : std_logic_vector(7 downto 0);
signal ADDR_INT : integer range 0 to 255;
signal ADDR_INT_DLY : integer range 0 to 255;

begin
	ADDR_INT <= conv_integer(RAM_ADDR);
	ADDR_INT_DLY <= conv_integer(RAM_ADDR_DLY2);
	process(CLK)
	begin
		if(CLK'event and CLK = '1') then
			if(ADDR_INT < 64) then
				RAM_OUT <= RAM_ARRAY(ADDR_INT);
			elsif(ADDR_INT = 65) then
				RAM_OUT <= IO65_IN;
			end if;
			if(RAM_WEN = '1') then
				if(ADDR_INT_DLY < 64) then
					RAM_ARRAY(ADDR_INT_DLY) <= RAM_IN;
				elsif(ADDR_INT_DLY = 64) then
					IO64_OUT <= RAM_IN;
				end if;
			end if;
			RAM_ADDR_DLY <= RAM_ADDR;
			RAM_ADDR_DLY2 <= RAM_ADDR_DLY;
		end if;
	end process;
end RTL;