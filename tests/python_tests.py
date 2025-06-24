import subprocess
from hashlib import sha512
import argparse
import random
import json

GREEN = "\033[92m"
RED = "\033[91m"
RESET = "\033[0m"


def run_sha512_implementation(input_value, input_type='s'):
    """
    Runs the C++ SHA-512 implementation and returns the hash output.
    """
    try:
        result = subprocess.run(
            ['./main', f'-{input_type}', input_value],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        if result.returncode != 0:
            raise RuntimeError(f"Error: {result.stderr.strip()}")
        return result.stdout.strip()
    except FileNotFoundError:
        raise RuntimeError("Executable './main' not found. Compile the project first.")


def custom_tests(test_plaintexts):
    test_vectors = []
    for plaintext in test_plaintexts:
        test_vectors.append({"input": plaintext, "expected": sha512(plaintext).hexdigest()})

    for vector in test_vectors:
        input_value = vector["input"]
        expected = vector["expected"]
        output = run_sha512_implementation(input_value).replace(" ", "")

        # Compare results
        if output != expected:
            print(f"{RED}Test failed for input: {vector['input']}")
            print(f"expected vs actual:")
            print(f"{expected}\n{output}{RESET}")
        else:
            print(f"{GREEN}Test passed for input: {vector['input']}{RESET}")

def random_tests(num_tests, seed=None):
    if seed is not None:
        random.seed(seed)
    else:
        random.seed()

    for iter in range(num_tests):
        input_value = bytes((1 + random.getrandbits(8) % 255) for _ in range((64 * iter) % (2048 + 1)))
        expected = sha512(input_value).hexdigest()
        output = run_sha512_implementation(input_value).replace(" ", "")

        # Compare results
        if output != expected:
            print(f"{RED}Random test {iter + 1} failed for input: {input_value}")
            print(f"expected vs actual:")
            print(f"{expected}\n{output}{RESET}")
        elif (iter + 1) % (num_tests / 20) == 0:
            print(f"{GREEN}Random test {iter + 1}/{num_tests} passed.{RESET}")


def test_vectors(json_file):
    try:
        with open(json_file, 'r') as f:
            test_vectors = json.load(f)
    except FileNotFoundError:
        raise RuntimeError(f"Test vector file '{json_file}' not found.")

    for vector in test_vectors:
        input_value = ""
        for _ in range(vector["message"]["count"]):
            input_value += vector["message"]["data"]
        expected = vector["SHA-512"]

        with open('temp', 'w') as temp_file:
            temp_file.write(input_value)

        output = run_sha512_implementation('temp', input_type='f').replace(" ", "")
        subprocess.run(['rm', 'temp'], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

        # Compare results
        if output != expected:
            print(f"{RED}Test failed for input: {vector['input'][:50]}")
            print(f"expected vs actual:")
            print(f"{expected}\n{output}{RESET}")
        else:
            input_str = str(input_value) if len(input_value) < 50 else str(input_value[:50]) + f"... ({len(input_value)} bytes)"
            print(f"{GREEN}Test passed for input: {input_str}{RESET}")


def test_sha512(num_tests=10, seed=None):
    print("=-=-=-=-= CUSTOM TESTS =-=-=-=-=")
    test_plaintexts = [b"", b"abc", b"The quick brown fox jumps over the lazy dog",
                       b"Lorem ipsum dolor sit amet, consectetur adipiscing elit.",
                       b"SHA-512 is a cryptographic hash function designed by the NSA.",
                       b"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",
                       b"1234567890!@#$%^&*()_+-=[]{}|;':\",.<>?/~`"]
    custom_tests(test_plaintexts)

    print("=-=-=-=-= RANDOM TESTS =-=-=-=-=")
    random_tests(num_tests, seed)

    print("=-=-=-=-= TEST VECTORS =-=-=-=-=-=")
    test_vectors("tests/sha_testvectors.json")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Run SHA-512 tests.")
    parser.add_argument('-n', '--num-tests', type=int, default=1000,
                        help='Number of random tests to run (default: 10)')
    parser.add_argument('-s', '--seed', type=int, default=None,
                        help='Seed for random number generator (default: None)')
    args = parser.parse_args()

    test_sha512(args.num_tests, args.seed)
