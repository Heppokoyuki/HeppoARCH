library IEEE;
use IEEE.std_logic_1164.all;

entity cpu15_slow is
	port
	(
		CLK : in std_logic;
		RESET_N : in std_logic;
		IO65_IN : in std_logic_vector(15 downto 0);
		IO64_OUT : out std_logic_vector(15 downto 0)
	);
end cpu15_slow;

architecture RTL of cpu15_slow is
component clk_down
	port (
		CLK_IN : in std_logic;
		CLK_OUT : out std_logic
	);
end component;

component cpu15_rom_ram
	port (
		CLK : in std_logic;
		RESET_N : in std_logic;
		IO65_IN : in std_logic_vector(15 downto 0);
		IO64_OUT : out std_logic_vector(15 downto 0)
	);
end component;

signal CLK_SLOW : std_logic;

begin
	C1 : clk_down
		port map(
			CLK_IN => CLK,
			CLK_OUT => CLK_SLOW
		);
		
	C2 : cpu15_rom_ram
		port map(
			CLK => CLK_SLOW,
			RESET_N => RESET_N,
			IO65_IN => IO65_IN,
			IO64_OUT => IO64_OUT
		);
end RTL;