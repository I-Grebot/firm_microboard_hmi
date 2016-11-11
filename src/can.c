/* -----------------------------------------------------------------------------
 * Microboard HMI
 * I-Grebot HMI board
 * -----------------------------------------------------------------------------
 * File        : can.c
 * Language    : C
 * Author      : Yannick C.
 * Date        : 2015-05-02
 * -----------------------------------------------------------------------------
 * Description
 *   This module handles robot CAN interface
 * -----------------------------------------------------------------------------
 * Versionning informations
 * Repository: http://svn2.assembla.com/svn/paranoid_andro96-id/
 * -----------------------------------------------------------------------------
 * $Rev::                                                                      $
 * $LastChangedBy::                                                            $
 * $LastChangedDate::                                                          $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Creation                                  Yannick C.   2015-05-02
 * -----------------------------------------------------------------------------
 */

#include "microBoard_hmi.h"
#include "igrecan_pl.h"

// -----------------------------------------------------------------------------
// GLOBALS
// -----------------------------------------------------------------------------

// CAN Configuration structure
can_cfg_t can_cfg ;

// Incomming CAN frames FIFO
// Placed in the fifo immediatly by the ISR routines,
// processed asynchroneously by the main function.
fifo_t* can_rx_fifo;

// Externs
//extern robot_t robot;

// -----------------------------------------------------------------------------
// INITIALIZATION
// -----------------------------------------------------------------------------

void microboardhmi_can_init(void) {
  
  // Define the CAN Processing function for RX messages
  can_cfg.can_process_rx = microboardhmi_can_rx;

  // Declare and allocate memory for CAN Software FIFOs
  can_rx_fifo = fifo_new(CAN_RX_FIFO_SIZE, sizeof(can_msg_t));

  // Setup CAN configuration and inits
  can_dma_config();
  can_init();
  can_isr_config();

  // All ID can be matched for filters using mask 0
  can_set_mask(CAN_MASK_0, CAN_MASK_NONE);

  // Associate each filter with a mask
  can_assoc_filter(0, CAN_MASK_0);

  // Enable the required filters
  can_enable_filter(0);
}

// -----------------------------------------------------------------------------
// CAN HANDLING FUNCTIONS
// -----------------------------------------------------------------------------

// Called whenever a new frame is received (ISR)
void microboardhmi_can_rx (void) {

  // Check to see if the TX FIFO is not full and place
  // the incomming frame in the queue
  if(!FIFO_IS_FULL(can_rx_fifo))
    fifo_push(can_rx_fifo, &(can_cfg.rx_msg));

} //  microboardhmi_can_rx

// -----------------------------------------------------------------------------
// CAN-RX FRAMES PROCESSOR
// -----------------------------------------------------------------------------

void do_can_rx(void) {
  can_msg_t rx_msg;
  payload_t rx_pl;

        //printf("do CAN\n");
  // Process all frames in the FIFO
  while(!FIFO_IS_EMPTY(can_rx_fifo)) {


    //printf("received message CAN\n");
    // Pull a message
    fifo_pull(can_rx_fifo, &rx_msg);

    // Send if over IGG
    //igg_process_can_rx(&rx_msg);

        printf("received CAN\n");
    // Local decoding for strategy execution
    switch(rx_msg.fid) {
      case CAN_FID_MOTION_GOTO:
        printf("received CAN_FID_MOTION_GOTO\n");
        break;

      case CAN_FID_MOTION_SET_SPEED:
        can_get_pl_motion_set_speed(&rx_msg, &rx_pl);
        printf("received CAN_FID_MOTION_SET_SPEED with speed_d = %d \n", rx_pl.motion_set_speed.speed_d);
        break;

      case CAN_FID_CLAP_CMD:
        can_get_pl_clap_cmd(&rx_msg, &rx_pl);
        printf("received CAN_FID_CLAP_CMD with left = %d and right = %d \n", rx_pl.clap_cmd.left_clap, rx_pl.clap_cmd.right_clap);
        break;

      case CAN_FID_SYSTEM_MATCH:
        can_get_pl_system_match(&rx_msg, &rx_pl);
        printf("received CAN_FID_SYSTEM_MATCH with values \n");
        printf("\t state : %d \n", rx_pl.system_match.state);
        printf("\t color : %d \n", rx_pl.system_match.color);
        printf("\t points : %d \n", rx_pl.system_match.points);
        printf("\t timestamp : %d \n", rx_pl.system_match.timestamp);
        
        if(0x00 == rx_pl.system_match.color)
        {
          LEDR = 1;
          LEDG = 1;
          LEDB = 0;
        }
        else if (0x01 == rx_pl.system_match.color)
        {
          LEDR = 0;
          LEDG = 1;
          LEDB = 0;
        }
        
        break;
    }
  }
}

// -----------------------------------------------------------------------------
// IGREGUI CAN-RX HANDLER
// -----------------------------------------------------------------------------

void igg_process_can_rx(can_msg_t* msg) {

}

// -----------------------------------------------------------------------------
// MOTION CAN SENDING SHORTHANDS
// -----------------------------------------------------------------------------

void can_send_motion_cmd(uint8_t flags, int16_t pos_reset_x, int16_t pos_reset_y,int16_t pos_reset_a) {
  can_msg_t msg_tx;
  payload_t pl;
  msg_tx.fid = CAN_FID_MOTION_COMMAND;
  msg_tx.pid = CAN_PID_DEFAULT;
  msg_tx.dlc = CAN_DLC_MOTION_COMMAND;
  msg_tx.rtr = 0;
  pl.motion_command.flags = flags;
  pl.motion_command.pos_reset_x = pos_reset_x;
  pl.motion_command.pos_reset_y = pos_reset_y;
  pl.motion_command.pos_reset_a = pos_reset_a;
  can_set_pl_motion_command(&msg_tx, &pl);
  can_send(&msg_tx);
}

void can_send_motion_goto(uint8_t type, int16_t pos_x,int16_t pos_y) {
  can_msg_t msg_tx;
  payload_t pl;
  msg_tx.fid = CAN_FID_MOTION_GOTO;
  msg_tx.pid = CAN_PID_DEFAULT;
  msg_tx.dlc = CAN_DLC_MOTION_GOTO;
  msg_tx.rtr = 0;
  pl.motion_goto.type  = type;
  pl.motion_goto.pos_x = pos_x;
  pl.motion_goto.pos_y = pos_y;
  can_set_pl_motion_goto(&msg_tx, &pl);
  can_send(&msg_tx);
}

void can_send_motion_turnto(uint8_t type, int16_t pos_x,int16_t pos_y) {
  can_msg_t msg_tx;
  payload_t pl;
  msg_tx.fid = CAN_FID_MOTION_TURNTO;
  msg_tx.pid = CAN_PID_DEFAULT;
  msg_tx.dlc = CAN_DLC_MOTION_TURNTO;
  msg_tx.rtr = 0;
  pl.motion_turnto.type  = type;
  pl.motion_turnto.pos_x = pos_x;
  pl.motion_turnto.pos_y = pos_y;
  can_set_pl_motion_turnto(&msg_tx, &pl);
  can_send(&msg_tx);
}

void can_send_motion_set_speed(int16_t speed_d, int16_t speed_a) {
  can_msg_t msg_tx;
  payload_t pl;
  msg_tx.fid = CAN_FID_MOTION_SET_SPEED;
  msg_tx.pid = CAN_PID_DEFAULT;
  msg_tx.dlc = CAN_DLC_MOTION_SET_SPEED;
  msg_tx.rtr = 0;
  pl.motion_set_speed.speed_d  = speed_d;
  pl.motion_set_speed.speed_a  = speed_a;
  can_set_pl_motion_set_speed(&msg_tx, &pl);
  can_send(&msg_tx);
}


// -----------------------------------------------------------------------------
// ACTUATORS CAN SENDING SHORTHANDS
// -----------------------------------------------------------------------------

void can_send_spot_cmd(uint8_t left_builder, uint8_t right_builder, uint8_t bull_bar) {
  can_msg_t msg_tx;
  payload_t pl;
  msg_tx.fid = CAN_FID_SPOT_CMD;
  msg_tx.pid = CAN_PID_DEFAULT;
  msg_tx.dlc = CAN_DLC_SPOT_CMD;
  msg_tx.rtr = 0;
  pl.spot_cmd.left_builder = left_builder;
  pl.spot_cmd.right_builder = right_builder;
  pl.spot_cmd.bull_bar = bull_bar;
  can_set_pl_spot_cmd(&msg_tx, &pl);
  can_send(&msg_tx);
}

void can_send_pop_cmd(uint8_t left_pop, uint8_t right_pop) {
  can_msg_t msg_tx;
  payload_t pl;
  msg_tx.fid = CAN_FID_POP_CMD;
  msg_tx.pid = CAN_PID_DEFAULT;
  msg_tx.dlc = CAN_DLC_POP_CMD;
  msg_tx.rtr = 0;
  pl.pop_cmd.left_pop = left_pop;
  pl.pop_cmd.right_pop = right_pop;
  can_set_pl_pop_cmd(&msg_tx, &pl);
  can_send(&msg_tx);
}

void can_send_clap_cmd(uint8_t left_clap, uint8_t right_clap) {
  can_msg_t msg_tx;
  payload_t pl;
  msg_tx.fid = CAN_FID_CLAP_CMD;
  msg_tx.pid = CAN_PID_DEFAULT;
  msg_tx.dlc = CAN_DLC_CLAP_CMD;
  msg_tx.rtr = 0;
  pl.clap_cmd.left_clap = left_clap;
  pl.clap_cmd.right_clap = right_clap;
  can_set_pl_clap_cmd(&msg_tx, &pl);
  can_send(&msg_tx);
}

void can_send_cup_cmd(uint8_t left_cup, uint8_t right_cup) {
  can_msg_t msg_tx;
  payload_t pl;
  msg_tx.fid = CAN_FID_CUP_CMD;
  msg_tx.pid = CAN_PID_DEFAULT;
  msg_tx.dlc = CAN_DLC_CUP_CMD;
  msg_tx.rtr = 0;
  pl.cup_cmd.left_cup = left_cup;
  pl.cup_cmd.right_cup = right_cup;
  can_set_pl_cup_cmd(&msg_tx, &pl);
  can_send(&msg_tx);
}


