
#include "hookapi.h"

#define ORACLE_ACCOUNT "rEXAMPL3ORACLEwALLE7ADDRESS0000000"
#define STATE_KEY "diesel_price"

int64_t hook(uint32_t reserved) {
    TRACE("Diesel Price Oracle Hook Triggered");

    // Only accept AccountSet TX from oracle
    if (otxn_type() != ttACCOUNT_SET) {
        TRACE("Rejected: Not AccountSet TX");
        return accept("Non-AccountSet TX ignored", 0);
    }

    // Verify sender is the oracle
    uint8_t acct[20];
    if (otxn_field(acct, 20, sfAccount) < 0) {
        TRACE("ERROR: Could not read Account field");
        return rollback(SBUF("Missing sender account"), 1);
    }

    // Oracle's account bytes
    uint8_t oracle_bytes[20];
    if (parse_account(ORACLE_ACCOUNT, oracle_bytes) < 0) {
        return rollback(SBUF("Oracle account parse failed"), 1);
    }

    // Check authorization
    if (BUFFER_EQUAL(acct, oracle_bytes, 20) != 1) {
        return rollback(SBUF("Unauthorized sender"), 1);
    }

    // Read diesel price from domain field (or Memo later)
    uint8_t domain_buf[32];
    int64_t len = otxn_field(domain_buf, sizeof(domain_buf), sfDomain);
    if (len <= 0) {
        return rollback(SBUF("Missing diesel price domain"), 1);
    }

    // Save diesel price into state
    if (state_set(domain_buf, len, STATE_KEY, sizeof(STATE_KEY) - 1) < 0) {
        return rollback(SBUF("Failed to store diesel price"), 1);
    }

    TRACEVAR("Updated Diesel Price: ", domain_buf);
    return accept(SBUF("Diesel price updated"), 0);
}
