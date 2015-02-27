/* 
 * File:   ccronexpr.h
 * Author: alex
 *
 * Created on February 24, 2015, 9:35 AM
 */

#ifndef CCRONEXPR_H
#define	CCRONEXPR_H

#include <time.h>

/**
 * Parsed cron expression
 */
typedef struct {
    char* seconds;
    char* minutes;
    char* hours;
    char* days_of_week;
    char* days_of_month;
    char* months;
} cron_expr;

/**
 * Parses specified cron expression.
 * 
 * @param expression cron expression as nul-terminated string,
 *        should be no longer that 256 bytes
 * @param error output error message, will be set to string literal
 *        error message in case of error. Will be set to NULL on success.
 *        The error message should NOT be freed by client.
 * @return parsed cron expression in case of success. Returned expression
 *        must be freed by client using 'cron_expr_free' function.
 *        NULL is returned on error.
 */
cron_expr* cron_parse_expr(const char* expression, const char** error);

/**
 * Uses the specified expression to calculate the next 'fire' date after
 * the specified date. All dates are processed as UTC (GMT) dates 
 * without timezones information.
 * 
 * For the same functionality but with local dates processing (using current
 * system timezone settings) use 'cron_next_local' function.
 * 
 * @param expr parsed cron expression to use in next date calculation
 * @param date start date to start calculation from
 * @return next 'fire' date in case of success, '((time_t) -1)' in case of error.
 */
time_t cron_next(cron_expr* expr, time_t date);

/**
 * Performs the same operations as 'cron_next' function, but use 
 * local dates processing (using current system timezone settings).
 * 
 * @param expr parsed cron expression to use in next date calculation
 * @param date start date to start calculation from
 * @return next 'fire' date in case of success, '((time_t) -1)' in case of error.
 */
time_t cron_next_local(cron_expr* expr, time_t date);

/**
 * Frees the memory allocated by the specified cron expression
 * 
 * @param expr parsed cron expression to free
 */
void cron_expr_free(cron_expr* expr);

#endif	/* CCRONEXPR_H */
