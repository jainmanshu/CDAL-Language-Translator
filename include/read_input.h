/*******************************************************************************
 * Name            : read_input.h
 * Project         : fcal
 * Module          : scanner
 * Description     : A utility to read the contents of a file into a
 *                   character buffer
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Eric Van Wyk
 * Modifications by: John Harwell
 ******************************************************************************/

#ifndef PROJECT_INCLUDE_READ_INPUT_H_
#define PROJECT_INCLUDE_READ_INPUT_H_

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace scanner {

/*******************************************************************************
 * Functions
 ******************************************************************************/
char *ReadInput(int argc, char **argv);
char *ReadInputFromFile(const char *filename);

} /* namespace scanner */
} /* namespace fcal */

#endif /* PROJECT_INCLUDE_READ_INPUT_H_ */
