library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;

entity fetch_rom_timequest is
	port (
		ADDR : in std_logic_vector(7 downto 0);
		CLK : in std_logic;
		Q2 : out std_logic_vector(14 downto 0)
	);
end fetch_rom_timequest;

architecture RTL of fetch_rom_timequest is

component fetch_rom
	port (
		address : in std_logic_vector(7 downto 0);
		clock : in std_logic;
		q : out std_logic_vector(14 downto 0)
	);
end component;

signal Q : std_logic_vector(14 downto 0);

begin
	C1 : fetch_rom port map(
		address => ADDR,
		clock => CLK,
		q => Q
	);
	
	process(CLK)
	begin
		if(CLK'event and CLK = '1') then
			Q2 <= Q;
		end if;
	end process;
end RTL;