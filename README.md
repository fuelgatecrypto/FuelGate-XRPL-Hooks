# FuelGate XRPL Hooks Suite

This repository contains a custom set of XRPL Hooks written in C for the **FuelGate Crypto** ecosystem, enabling advanced functionality for the **Fuel Transaction Coin (FTC)** token:

- **Diesel Oracle Hook**: Updates diesel price data via memos.
- **Burn Vault Hook**: Implements a deflationary mechanism by burning 1.5% of every FTC payment.
- **Customer Rewards & Liquidity Tracker Hook**: Tracks loyalty and rewards token holders based on activity.

---

## Hooks Overview

### 1. Diesel Oracle Hook
**File**: `diesel_oracle_hook.c`  
**Purpose**: Updates diesel prices using memo fields in transactions.

**How It Works**:
- Listens for memos formatted as: `price:123.45`
- Converts the price into a fixed-point format and stores it in Hook state.
- Stores the current ledger time to validate price freshness.

**Key Features**:
- Creates a live price bridge between diesel fuel and FTC.
- Ensures stale price data is never used downstream.

---

### 2. Burn Vault Hook
**File**: `burn_vault_hook.c`  
**Purpose**: Burns 1.5% of every FTC transaction to XRPL’s null address (`rrrrrrrrrrrrrrrrrrrrrhoLvTp`).

**How It Works**:
- Triggers on FTC **PAYMENT** transactions.
- Validates that the diesel price is fresh (within the past hour).
- Calculates and burns 1.5% of the payment amount.

**Key Features**:
- Makes FTC deflationary with every transaction.
- Maintains price integrity by relying on the latest oracle data.

---

### 3. Customer Rewards & Liquidity Tracker Hook
**File**: `customer_rewards_hook.c`  
**Purpose**: Tracks FTC usage per wallet and rewards loyal users with REWARD tokens.

**How It Works**:
- Activates on FTC **PAYMENT** transactions.
- Tracks wallet activity and tallies loyalty points.
- Distributes REWARD tokens when thresholds are hit.

**Key Features**:
- Boosts user engagement and ecosystem stickiness.
- Enables analytics around token velocity and distribution.

---

## Deployment Instructions

### Requirements

1. **XRPL Server**: Spin up a testnet node using `xrpld`.
2. **Hooks SDK**: Install the official [xrpl-hooks](https://hooks.xrpl.org/) SDK for compiling/deploying Hooks.

---

### Build and Deploy

```bash
# Clone the repo
git clone https://github.com/your-org/fuelgate-xrpl-hooks.git
cd fuelgate-xrpl-hooks

# Compile each Hook
hookc diesel_oracle_hook.c -o diesel_oracle.wasm
hookc burn_vault_hook.c -o burn_vault.wasm
hookc customer_rewards_hook.c -o customer_rewards.wasm

# Deploy Hooks to XRPL (example)
hookset deploy --account <your_xrpl_account> --wasm diesel_oracle.wasm --namespace diesel.oracle.fuelgate
hookset deploy --account <your_xrpl_account> --wasm burn_vault.wasm --namespace burn.vault.fuelgate
hookset deploy --account <your_xrpl_account> --wasm customer_rewards.wasm --namespace rewards.tracker.fuelgate
