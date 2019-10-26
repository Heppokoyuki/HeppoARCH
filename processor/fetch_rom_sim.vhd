library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;

entity fetch_rom_sim is
end fetch_rom_sim;

architecture SIM of fetch_rom_sim is

component fetch_rom
	port (
		address : in std_logic_vector(7 downto 0);
		clock : in std_logic;
		q : out std_logic_vector(14 downto 0)
	);
end component;

signal ADDRESS : std_logic_vector(7 downto 0);
signal CLK : std_logic;
signal Q : std_logic_vector(14 downto 0);

begin
	C1 : fetch_rom port map(
		address => ADDRESS,
		clock => CLK,
		q => Q
	);
	
	process begin
		CLK <= '0';
		wait for 10 ns;
		CLK <= '1';
		wait for 10 ns;
	end process;
	
	process begin
		ADDRESS <= "00000000";
		for I in 0 to 15 loop
			wait for 20 ns;
			ADDRESS <= ADDRESS + 1;
		end loop;
		wait;
	end process;
end SIM;