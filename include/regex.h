/*******************************************************************************
 * Name            : regex.h
 * Project         : Labs
 * Module          : Lab03
 * Description     : Header file for regex module
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Eric Van Wyk
 * Modifications by: John Harwell
 ******************************************************************************/

#ifndef PROJECT_INCLUDE_REGEX_H_
#define PROJECT_INCLUDE_REGEX_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <regex.h>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace scanner {

/*******************************************************************************
 * Constant Definitions
 ******************************************************************************/
const int kRegexNSub = 1;

/*******************************************************************************
 * Forward Declarations
 ******************************************************************************/
regex_t *make_regex(const char* pattern);
int match_regex(regex_t *, const char *);

} /* namespace scanner */
} /* namespace fcal */

#endif /* PROJECT_INCLUDE_REGEX_H_ */
