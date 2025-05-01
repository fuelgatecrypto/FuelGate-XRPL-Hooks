# FuelGate XRPL Hooks Suite

This repository contains a custom set of XRPL Hooks written in C for the FuelGate Crypto ecosystem, enabling advanced functionality for the Fuel Transaction Coin (FTC) token:

- **Diesel Oracle Hook**: Updates diesel price data via memos.
- **Burn Vault Hook**: Implements a deflationary mechanism by burning 1.5% of every FTC payment.
- **Customer Rewards & Liquidity Tracker Hook**: Tracks loyalty and rewards token holders based on activity.

## Hooks Overview

### 1. Diesel Oracle Hook
**File**: `diesel_oracle_hook.c`  
**Purpose**: Updates diesel prices using memo fields in transactions.  
**How It Works**:
- Listens for memos formatted as: `price:123.45`
- Converts the price into a fixed-point format and stores it in Hook state
- Saves the current ledger time to ensure real-time price accuracy

**Key Features**:
- Ensures dynamic linkage between FTC and real-world diesel prices
- Prevents outdated price data from being used by other Hooks

### 2. Burn Vault Hook
**File**: `burn_vault_hook.c`  
**Purpose**: Burns 1.5% of every FTC transaction to XRPL’s null address (`rrrrrrrrrrrrrrrrrrrrrhoLvTp`).  
**How It Works**:
- Activates on FTC PAYMENT transactions
- Verifies the diesel price has been updated within the last hour
- Calculates 1.5% of the transferred amount and burns it

**Key Features**:
- Implements a deflationary mechanism for FTC
- Maintains synchronization with real-world diesel prices

### 3. Customer Rewards & Liquidity Tracker Hook
**File**: `customer_rewards_hook.c`  
**Purpose**: Tracks FTC payments per wallet and rewards loyalty with REWARD tokens.  
**How It Works**:
- Monitors FTC PAYMENT transactions
- Tracks customer activity and accumulates loyalty points
- Issues REWARD tokens when thresholds are met

**Key Features**:
- Encourages long-term engagement with FTC
- Provides insights into liquidity flow within the ecosystem

## Deployment Instructions

### Requirements
1. XRPL Server: Set up an XRPL Testnet environment using `xrpld`
2. Hooks SDK: Install the `xrpl-hooks` SDK for compiling and deploying Hooks

### Build and Deploy

```bash
git clone https://github.com/your-org/fuelgate-xrpl-hooks.git
cd fuelgate-xrpl-hooks

hookc diesel_oracle_hook.c -o diesel_oracle.wasm
hookc burn_vault_hook.c -o burn_vault.wasm
hookc customer_rewards_hook.c -o customer_rewards.wasm

hookset deploy --account <your_xrpl_account> --wasm diesel_oracle.wasm --namespace diesel.oracle.fuelgate
hookset deploy --account <your_xrpl_account> --wasm burn_vault.wasm --namespace burn.vault.fuelgate
hookset deploy --account <your_xrpl_account> --wasm customer_rewards.wasm --namespace rewards.tracker.fuelgate
```

## Sample Manifest

```json
[
  {
    "hook_namespace": "diesel.oracle.fuelgate",
    "hook_on": "hook_on_memo",
    "file": "diesel_oracle_hook.c"
  },
  {
    "hook_namespace": "burn.vault.fuelgate",
    "hook_on": "hook_on_ftc_payment",
    "file": "burn_vault_hook.c"
  },
  {
    "hook_namespace": "rewards.tracker.fuelgate",
    "hook_on": "hook_on_ftc_payment",
    "file": "customer_rewards_hook.c"
  }
]
```

## License
MIT License

## Credits
Crafted for the FuelGate Crypto (FGC) + Fuel Transaction Coin (FTC) project by Philhein.
