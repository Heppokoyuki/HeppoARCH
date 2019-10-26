library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;

entity n_reg_ex is
	port(
		CLK_EX : in std_logic;
		N_REG : in std_logic_vector(2 downto 0);
		N_REG_DLY : out std_logic_vector(2 downto 0)
	);
end n_reg_ex;

architecture RTL of n_reg_ex is
begin
	process(CLK_EX)
	begin
		if(CLK_EX'event and CLK_EX = '1') then
			N_REG_DLY <= N_REG;
		end if;
	end process;
end RTL;