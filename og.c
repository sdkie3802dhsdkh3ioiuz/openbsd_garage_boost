/* og.c -- power relay briefly in order to open garage door
 *
 * Copyright(c) 2021 Sven G
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA
 * OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <err.h>
#include <sys/gpio.h>
#include <sysioctl.h>
#include <fcntl.h>

#define DOOR_PIN 23
#define NANOSLEEP 500000000	/* half a second */

int main() {
	struct gpio_pin_op op;
	struct timespec timeout;
	timeout.tv_nsec = NANOSLEEP;
	timeout.tv_sec = 0;
	int devfd = open("/dev/gpio0", O_RDWR);

	/* Trick garage wall console into thinking
	 * button was pressed.
	 */
	memset(&op, 0, sizeof(op));
	op.gp_pin = DOOR_PIN;
	op.gp_value = GPIO_PIN_HIGH;
	ioctl(devfd, GPIOPINWRITE, &op);

	/* Let time elapse. */
	nanosleep(&timeout, NULL);

	/* Trick garage wall console into thinking
	 * button was released.
	 */
	memset(&op, 0, sizeof(op));
	op.gp_pin = DOOR_PIN;
	op.gp_value = GPIO_PIN_LOW;
	ioctl(devfd, GPIOPINWRITE, &op);

	return 0;
}
