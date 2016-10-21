@if(isset($errors) && !empty($errors->first()))
    <div class="alert alert-danger " role="alert">
        <button type="button" class="close" data-dismiss="alert" aria-label="Close"><span aria-hidden="true">&times;</span></button>
        <strong>错误!</strong>
        {{$errors->first()}}
    </div>
@endif

@if(isset($msg_notify) && !empty($msg_notify))
    <div class="alert alert-info " role="alert">
        <button type="button" class="close" data-dismiss="alert" aria-label="Close"><span aria-hidden="true">&times;</span></button>
        {{$msg_notify}}
    </div>
@endif

@if(session('msg_notify'))
    <div class="alert alert-info " role="alert">
        <button type="button" class="close" data-dismiss="alert" aria-label="Close"><span aria-hidden="true">&times;</span></button>
        {{session('msg_notify')}}
    </div>
@endif