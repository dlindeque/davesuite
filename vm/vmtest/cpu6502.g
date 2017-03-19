Scenario: cpu6502_addressing_mode_immediate
    Given a 6502 cpu in 'slot1' with the following state
    | Register | Value                       |
    | A        | 0x0F                        |
    | Y        | 0x00                        |
    | X        | 0x00                        |
    | PC       | 0x0200                      |
    | S        | 0x00                        |
    | P        | N=0;V=0;B=0;D=0;I=0;Z=0;C=0 |
    And a mock ram
    And the following program
    """
    .ORG $0200
    AND #$11   ; And accumulator with 0x11
    LDA #$01   ; Load accumulator with 0x01
    STA #$C000 ; Store A into 0xC000
    """
    When I cycle the clock until 0xC000 is not 0x00
    Then I expect the following state in the 6502 cpu in 'slot1'
    | Register | Value                       |
    | A        | 0x01                        |
    | Y        | 0x00                        |
    | X        | 0x00                        |
    | PC       | 0x0202                      |
    | S        | 0x00                        |
    | P        | N=0;V=0;B=0;D=0;I=0;Z=0;C=0 |
    And I expect the ram to be zero for all but
    | Address | Value |
    | 0xC000  | 0x01  |

Scenario: cpu6502_addressing_mode_absolute
    Given a 6502 cpu in 'slot1' with the following state
    | Register | Value                       |
    | A        | 0x0F                        |
    | Y        | 0x00                        |
    | X        | 0x00                        |
    | PC       | 0x0200                      |
    | S        | 0x00                        |
    | P        | N=0;V=0;B=0;D=0;I=0;Z=0;C=0 |
    And a mock ram
    And the following program
    """
    .ORG $0200
    AND $0308 ; And accumulator with data (0x22) at 0x0308
    .ORG $0308
    .BYTE $22
    """
    When I pulse the clock to process the next instruction
    Then I expect the following process state
    | Register | Value                       |
    | A        | 0x02                        |
    | Y        | 0x00                        |
    | X        | 0x00                        |
    | PC       | 0x0203                      |
    | S        | 0x00                        |
    | P        | N=0;V=0;B=0;D=0;I=0;Z=0;C=0 |
    And I expect no changes to the ram
