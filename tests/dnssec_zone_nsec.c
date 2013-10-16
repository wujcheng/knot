/*  Copyright (C) 2013 CZ.NIC, z.s.p.o. <knot-dns@labs.nic.cz>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <config.h>
#include <tests/tap/basic.h>

#include "libknot/dname.h"
#include "libknot/dnssec/zone-nsec.h"

static knot_dname_t *get_dname(const char *str)
{
	size_t length = strlen(str);
	return knot_dname_from_str(str, length);
}

int main(int argc, char *argv[])
{
	plan(1);

	knot_dname_t *owner  = get_dname("name.example.com");
	knot_dname_t *apex   = get_dname("example.com");
	knot_dname_t *expect = get_dname("sv9o5lv8kgv6lm1t9dkst43b3c0aagbj.example.com");

	knot_nsec3_params_t params = {
		.algorithm = 1, .flags = 0, .iterations = 10,
		.salt = (uint8_t *)"\xc0\x01", .salt_length = 2
	};

	knot_dname_t *result = create_nsec3_owner(owner, apex, &params);
	is_int(0, knot_dname_cmp(result, expect), "create_nsec3_owner()");

	knot_dname_free(&result);
	knot_dname_free(&owner);
	knot_dname_free(&apex);
	knot_dname_free(&expect);

	return 0;
}
