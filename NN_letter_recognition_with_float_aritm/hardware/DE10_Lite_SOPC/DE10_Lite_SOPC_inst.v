	DE10_Lite_SOPC u0 (
		.clk_clk                                          (<connected-to-clk_clk>),                                          //                                       clk.clk
		.clk_sdram_clk                                    (<connected-to-clk_sdram_clk>),                                    //                                 clk_sdram.clk
		.clk_vga_clk                                      (<connected-to-clk_vga_clk>),                                      //                                   clk_vga.clk
		.lcd_reset_n_external_connection_export           (<connected-to-lcd_reset_n_external_connection_export>),           //           lcd_reset_n_external_connection.export
		.lt24_controller_conduit_end_lt24_cs              (<connected-to-lt24_controller_conduit_end_lt24_cs>),              //               lt24_controller_conduit_end.lt24_cs
		.lt24_controller_conduit_end_lt24_rs              (<connected-to-lt24_controller_conduit_end_lt24_rs>),              //                                          .lt24_rs
		.lt24_controller_conduit_end_lt24_rd              (<connected-to-lt24_controller_conduit_end_lt24_rd>),              //                                          .lt24_rd
		.lt24_controller_conduit_end_lt24_wr              (<connected-to-lt24_controller_conduit_end_lt24_wr>),              //                                          .lt24_wr
		.lt24_controller_conduit_end_lt24_data            (<connected-to-lt24_controller_conduit_end_lt24_data>),            //                                          .lt24_data
		.pio_key_external_connection_export               (<connected-to-pio_key_external_connection_export>),               //               pio_key_external_connection.export
		.pio_led_external_connection_export               (<connected-to-pio_led_external_connection_export>),               //               pio_led_external_connection.export
		.pio_sw_external_connection_export                (<connected-to-pio_sw_external_connection_export>),                //                pio_sw_external_connection.export
		.reset_reset_n                                    (<connected-to-reset_reset_n>),                                    //                                     reset.reset_n
		.sdram_wire_addr                                  (<connected-to-sdram_wire_addr>),                                  //                                sdram_wire.addr
		.sdram_wire_ba                                    (<connected-to-sdram_wire_ba>),                                    //                                          .ba
		.sdram_wire_cas_n                                 (<connected-to-sdram_wire_cas_n>),                                 //                                          .cas_n
		.sdram_wire_cke                                   (<connected-to-sdram_wire_cke>),                                   //                                          .cke
		.sdram_wire_cs_n                                  (<connected-to-sdram_wire_cs_n>),                                  //                                          .cs_n
		.sdram_wire_dq                                    (<connected-to-sdram_wire_dq>),                                    //                                          .dq
		.sdram_wire_dqm                                   (<connected-to-sdram_wire_dqm>),                                   //                                          .dqm
		.sdram_wire_ras_n                                 (<connected-to-sdram_wire_ras_n>),                                 //                                          .ras_n
		.sdram_wire_we_n                                  (<connected-to-sdram_wire_we_n>),                                  //                                          .we_n
		.seg7_conduit_end_export                          (<connected-to-seg7_conduit_end_export>),                          //                          seg7_conduit_end.export
		.touch_panel_busy_external_connection_export      (<connected-to-touch_panel_busy_external_connection_export>),      //      touch_panel_busy_external_connection.export
		.touch_panel_pen_irq_n_external_connection_export (<connected-to-touch_panel_pen_irq_n_external_connection_export>), // touch_panel_pen_irq_n_external_connection.export
		.touch_panel_spi_external_MISO                    (<connected-to-touch_panel_spi_external_MISO>),                    //                  touch_panel_spi_external.MISO
		.touch_panel_spi_external_MOSI                    (<connected-to-touch_panel_spi_external_MOSI>),                    //                                          .MOSI
		.touch_panel_spi_external_SCLK                    (<connected-to-touch_panel_spi_external_SCLK>),                    //                                          .SCLK
		.touch_panel_spi_external_SS_n                    (<connected-to-touch_panel_spi_external_SS_n>)                     //                                          .SS_n
	);

