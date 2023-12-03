<script lang="ts">
    import { type TableSource, Table } from "@skeletonlabs/skeleton";
    import { tableMapperValues } from "@skeletonlabs/skeleton";

    export let ambientTemp;
    export let motorTemp;
    export let latitude;
    export let longitude;

    const tableData = [
        {position: 1, dato: "Temp Ambiente", valor: ambientTemp },
        {position: 1, dato: "Temp Motor", valor: motorTemp },
        {position: 1, dato: "Latitud", valor: latitude},
        {position: 1, dato: "Longitud", valor: longitude },
    ]


    const tableSimple: TableSource = {
        // A list of heading labels.
        head: ['Dato', 'Valor'],
        // The data visibly shown in your table body UI.
        body: tableMapperValues(tableData, ['dato', 'valor']),
    };
                    
</script>

<div class="m-4 shadow-lg">
    <Table source={tableSimple} />
</div>
