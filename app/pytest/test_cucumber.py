import logging
import os
import subprocess

TEST_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def test_srs(dut):
    logging.info("Starting Cucumber...")
    cucumber = subprocess.run(
        [
            "cucumber",
            "--strict",
            "--publish-quiet",
        ],
        cwd=TEST_DIR,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
    )
    logging.info(f"Cucumber returned with code {cucumber.returncode}.")
    logging.info(f"Cucumber output:\n\n{cucumber.stdout}")
    assert cucumber.returncode == 0
